#include <iostream>
#include <map>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include <curl/curl.h>

#include "pugixml/pugixml.hpp"

#include "ofxget.h"

namespace ofx_get {

using std::cout;
using std::endl;
using std::map;
using std::ostream;
using std::string;
using std::vector;

struct AppInfo {
  AppInfo(const string& n, const string& id, const string& ver) {
    name = n;
    appid = id;
    appver = ver;
  }

  string name;
  string appid;
  string appver;
};

std::vector<AppInfo> g_apps {
  AppInfo("Money_2007", "MONEY", "1600"),
  AppInfo("Quicken_2005", "QWIN", "1400"),
  AppInfo("Quicken_2010", "QWIN", "1800"),
  AppInfo("Quicken_2011", "QWIN", "1900"),
  AppInfo("Quicken_2016", "QWIN", "2500"),
  AppInfo("QuickBooks_2008", "QBW", "1800"),
};

static size_t CurlWriteToString(char *ptr, size_t size, size_t nmemb,
                                void *userdata) {
  if (size != 1) {
    char err[255];
    sprintf(err, "In CurlWriteToString, expected char size 1, got %ld", size);
    throw string(err);
  }
  string* out = static_cast<string*>(userdata);
  string to_add;
  to_add.resize(nmemb);
  memcpy((void*) to_add.c_str(), (void*) ptr, nmemb);
  *out += to_add;
  return size * nmemb;
}

size_t HeaderCallback(char *ptr, size_t size, size_t nmemb,
                      void *userdata) {
  if (size != 1) {
    char err[255];
    sprintf(err, "In HeaderCallback, expected char size 1, got %ld", size);     throw string(err);
  }
  string* out = static_cast<string*>(userdata);
  string to_add;
  to_add.resize(nmemb);
  memcpy((void*) to_add.c_str(), (void*) ptr, nmemb);
  *out += to_add;
  return size * nmemb;
}

bool PostRequest(const std::string& request, const std::string& url,
                 std::string* response, std::string* headers)
{
  *headers = "";
  *response = "";
  CURL *curl = curl_easy_init();
  if (! curl) {
    throw std::string("Could not initialize curl");
  }

  // Convert to \r\n format
  std::regex to_rn("\r\n|\n", std::regex_constants::extended);
  string rn_request = regex_replace(request, to_rn, "\r\n");

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, rn_request.c_str());

  struct curl_slist *headerlist = NULL;
  headerlist = curl_slist_append(headerlist, "Content-type: application/x-ofx");
  headerlist = curl_slist_append(headerlist, "Accept: */*, application/x-ofx");

  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteToString);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) response);
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void*) headers);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, REQUEST_TIMEOUT /* seconds */);
  CURLcode res = curl_easy_perform(curl);

  curl_easy_cleanup(curl);
  curl_slist_free_all(headerlist);

  if (res != CURLE_OK) {
      throw "Curl error: " + string(curl_easy_strerror(res));
  }

  return response->find("OFXHEADER") != string::npos;
}

string OfxDate() {
  time_t now = time(nullptr);
  struct tm* ltime = localtime(&now);
  char time_str[255];
  sprintf(time_str, "%04d%02d%02d%02d%02d%02d.000",
          1900 + ltime->tm_year, 1 + ltime->tm_mon, ltime->tm_mday,
          ltime->tm_hour, ltime->tm_min, ltime->tm_sec);
  return time_str;
}

void InitVars(VarsMap* vars) {
  vars->clear();
  (*vars)["OFXDATE"] = OfxDate();
}

string SubstituteVars(const string& s, const VarsMap& vars) {
  string subbed = s;
  for (std::size_t i = 0; i < subbed.size(); i++) {
    if (subbed[i] == '$') {
      std::size_t j;
      for (j = i + 1; j < subbed.size(); j++) {
        if (!isupper(subbed[j])) {
          break;
        }
      }
      string var = subbed.substr(i + 1, j - i - 1);
      VarsMap::const_iterator it = vars.find(var);
      if (it != vars.end()) {
        subbed.replace(i, j - i, it->second);
      } else {
        throw "Unspecified variable: " + var;
      }
    }
  }
  return subbed;
}

string GetRequestTemplate(const string& filename) {
  std::ifstream f(filename);
  if (!f.is_open()) {
    throw "Could not open " + filename;
  }

  string line;
  string request_template;
  while (std::getline(f, line)) {
    request_template += line + "\r\n";
  }

  return request_template;
}

vector<string> GetMissingRequestVars(const string& request_template,
                                     const VarsMap& vars) {
  vector<string> missing;
  for (std::size_t i = 0; i < request_template.size(); i++) {
    if (request_template[i] == '$') {
      std::size_t j;
      for (j = i + 1; j < request_template.size(); j++) {
        if (!isupper(request_template[j])) {
          break;
        }
      }
      string var = request_template.substr(i + 1, j - i - 1);
      VarsMap::const_iterator it = vars.find(var);
      if (it == vars.end() || it->second.empty()) {
        missing.push_back(var);
      }
    }
  }
  return missing;
}

string BuildRequest(const string& request_template, const VarsMap& vars) {
  return SubstituteVars(request_template, vars);
}

void AddApp(VarsMap* vars, const string& name) {
  for (std::size_t i = 0; i < g_apps.size(); i++) {
    if (g_apps[i].name == name) {
      (*vars)["APPID"] = g_apps[i].appid;
      (*vars)["APPVER"] = g_apps[i].appver;
      return;
    }
  }
  throw "Unknown app " + name;
}

void AddInstitution(int id, VarsMap* vars) {
  std::string id_str = std::to_string(id);
  string filename = "institutions.txt";
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(filename.c_str());
  if (!result) {
    throw "Could not parse " + filename;
  }
  auto inst = doc.find_child_by_attribute("institution", "id", id_str.c_str());
  if (inst.empty()) {
    throw "Could not find institution " + id_str;
  }
  std::vector<string> var_names {"org", "fid", "brokerid", "bankid", "url"};
  for (string name : var_names) {
    auto var = inst.child(name.c_str());
    if (var) {
      for (std::size_t i = 0; i < name.size(); i++) {
        name[i] = toupper(name[i]);
      }
      (*vars)[name] = var.child_value();
    }
  }
}

void AddPasswords(int id, const char* filename, VarsMap* vars) {
  std::string id_str = std::to_string(id);
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(filename);
  if (!result) {
    return;
  }
  auto inst = doc.find_child_by_attribute("institution", "id", id_str.c_str());
  if (inst.empty()) {
    return;
  }
  for (auto node : inst) {
    (*vars)[node.name()] = node.child_value();
  }
}

}  // namespace ofx_get
