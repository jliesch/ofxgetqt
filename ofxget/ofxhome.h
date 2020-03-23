#ifndef OFXHOME_H
#define OFXHOME_H

#include <map>
#include <string>
#include <vector>

namespace ofx_get {

struct Institution {
    int ofxhome_id;
    std::string name;
    std::string fid;
    std::string org;
    std::string url;
    int ofxfail;
    int sslfail;
    std::string lastofxvalidation;
    std::string lastsslvalidation;
    std::string brokerid;
    std::string bankid;
    std::map<std::string, std::string> profile;

    friend std::ostream& operator<<(std::ostream& stream,
                                    const Institution& inst);
};

std::string OfxHomeFullDumpString();

std::vector<Institution> OfxDumpStringToInstitutions(const std::string& dump);

const Institution* FindInstitutionByName(
    const std::vector<Institution>& institutions,
    const std::string& name);

// Returns true if the api_key is avalid.
bool ValidateApiKey(const std::string& api_key);

// Uploads a successful request to OFX Home. The request string will be sanitized
// server side, however, to be safe AnonymizeRequest is called beforehand.
std::string UploadSuccessfulRequest(
    const std::string& api_key, const std::string& url,
    const std::string& request);

// Removes any personal information from USERID, ACCTID, and USERPASS fields.
std::string AnonymizeRequest(const std::string& request);

}  // namespace ofx_get

#endif // OFXHOME_H
