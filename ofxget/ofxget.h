#ifndef __OFX_GET_H__
#define __OFX_GET_H__

// ofxget is a small library for building OFX requests and downloading OFX
// responses from institutions. It is intentionally lightweight and simple.
//
// A simple use of the library is as follows:
//
//   try {
//     VarsMap vars;
//     InitVars(&vars);
//     AddApp(&vars, "QuickBooks_2008");
//     AddInstitution(479, &vars);  // 479 is Vanguard
//     AddPasswords(479, "passwords.txt", &vars);
//     // or vars["USERID"] = "user", etc.
//     
//     string request = BuildRequest(
//       GetRequestTemplate("requests/" + string(request_filename)), vars);
//     string response = PostRequest(request, vars["URL"]);
//     cout << "RESPONSE" << endl << endl << response << endl;
//   } catch(const string& msg) {
//     cout << msg << endl;
//   }

#include <map>
#include <string>

#include "ofxhome.h"

namespace ofx_get {

// Request timeout when posting requests in seconds.
#define REQUEST_TIMEOUT 10

// VarsMap is one half of the data used for building a request. The other is the
// request template. VarsMap contains all of the variables that will be
// substituted into the request. For example, VarMap["USERID"] = "myid".
typedef std::map<std::string, std::string> VarsMap;

// Initialize a vars map with common variables needed to send an OFX request.
void InitVars(VarsMap* vars);

// Add application vars to a VarsMap. Using "Quicken_2011" is a safe bet.
void AddApp(VarsMap* vars, const std::string& name);

// Add institution vars to a VarsMap. The id value refers to an institution in
// the institutions.txt file.
void AddInstitution(int id, VarsMap* vars);

// Add user passwords and other account info to a VarsMap. These values are read
// from a plain text file. This is not safe and should only be used for testing
// purposes.
void AddPasswords(int id, const char* filename, VarsMap* vars);

// Read a request template from a file (eg, investment.txt).
std::string GetRequestTemplate(const std::string& filename);

// Return a vector of all the request vars that are missing.
std::vector<std::string> GetMissingRequestVars(
        const std::string& request_template, const VarsMap& vars);

// Substitute the vars into a request template. A fully working request is
// returned.
std::string BuildRequest(const std::string& request_template, const VarsMap& vars);

// Send a request to an OFX server. url can be taken from a VarsMap using the
// URL key if the institution was loaded from AddInstitution. Returns true if
// the request is successful. This indicates that valid OFX was returned, not
// that authentication was successful.
bool PostRequest(const std::string& request, const std::string& url,
                 std::string* response, std::string* headers);

}  // namespace ofx_get

#endif /* __OFX_GET_H__ */
