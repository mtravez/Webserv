
#include "Request.hpp"
#include "utils.hpp"


// void appendStringToVector(std::vector<char> &vector, const char *str) {
//     if (str) {
//         std::string temp(str);
//         vector.insert(vector.end(), temp.begin(), temp.end());
//     }
// }

// std::string formatModificationTime(time_t modifTime) {
// 	struct tm* timeinfo = localtime(&modifTime);
// 	char timeStr[20];
// 	strftime(timeStr, sizeof(timeStr),"%d-%m-%Y %H:%M", timeinfo);
// 	return std::string(timeStr);
// }

// std::string formatSize(off_t size) {
// 	const char * suffix[] = {"", "KB", "MB", "GB", "TB"};
// 	int	index = 0;
// 	double sizeInUnits = static_cast<double>(size);
// 	while (sizeInUnits >= 1024 && index < 4) {
// 		sizeInUnits /= 1024;
// 		++index;
// 	}
// 	std::ostringstream formatted;
// 	if (fmod(sizeInUnits, 1.0) != 0.0)
//         formatted << std::fixed << std::setprecision(1);
//     else
//         formatted << std::fixed << std::setprecision(0);
// 	formatted << sizeInUnits << suffix[index];
// 	return formatted.str();

// }
// void appendHtmlHead(std::string& requestPath, std::vector<char>& _body) {
// 	appendStringToVector(_body, "<!DOCTYPE html>"
// 								"<html lang=\"en\">"
// 								"<head>"
// 								"<meta charset=\"UTF-8\">"		
// 								"<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">"
// 								"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
// 								"<title>Index of ");
// 	_body.insert(_body.end(), requestPath.begin(), requestPath.end());
// 	appendStringToVector(_body, "</title>"
// 								"<style>"
// 								"main {display: flex;flex-direction: column;width: 90vw;margin-top: 2em;gap: 0.5em;}"
// 								".rows {display: flex;flex-direction: row;width: 100%;}"
// 								".rows * {margin: 0;width: calc(100%/3);}"
// 								"hr {border: 1px solid #ccc;margin: 1em 0;}"
// 								"</style></head>");
					
// }

// void appendHtmlBodyStart(std::string& requestPath, std::vector<char>& _body) {
// 	appendStringToVector(_body, "<body><main>"
// 								"<h1>Index of ");
// 	_body.insert(_body.end(), requestPath.begin(), requestPath.end());
// 	appendStringToVector(_body, "</h1>"
// 								"<hr>");
// }

// void appendHtmlRow(std::string& fullPath, std::string& subPath, std::string& modTime, std::string& bytes, std::vector<char>& _body) {
// 	appendStringToVector(_body, "<div class=\"rows\">"
// 								"<a href=\"/");
// 	_body.insert(_body.end(), fullPath.begin(), fullPath.end());
// 	_body.push_back('/');
// 	_body.insert(_body.end(), subPath.begin(), subPath.end());
// 	appendStringToVector(_body, "\">");
// 	_body.insert(_body.end(), subPath.begin(), subPath.end());
// 	appendStringToVector(_body, "</a>"
// 								"<p>");
// 	_body.insert(_body.end(), modTime.begin(), modTime.end());
// 	appendStringToVector(_body, "</p>"
// 								"<p>");
// 	_body.insert(_body.end(), bytes.begin(), bytes.end());		
// 	appendStringToVector(_body, "</p></div>");
// }

// void appendHtmlEnd(std::vector<char>& _body) {
// 	appendStringToVector(_body, "</main></body></html>");
// }

// void makeDirectoryListing(std::string& path, std::string& requestPath, std::vector<char>& _body) {
// 	appendHtmlHead(requestPath, _body);
// 	appendHtmlBodyStart(requestPath, _body);
// 	DIR *dir = opendir(path.c_str());
//     if (dir == NULL) {
//         exit (1);	
//     }
//     struct dirent *dp;
//     while ((dp = readdir(dir)) != NULL) {
// 		if (dp->d_name[0] == '.' && dp->d_name[1] != '.')
// 			continue ;
// 		struct stat pathStat;
// 		std::string fullPath = path + "/" + dp->d_name;
// 		if (stat(fullPath.c_str(), &pathStat) != 0) 
// 			exit (1);
// 		std::string name(dp->d_name);
// 		std::string timeStr = formatModificationTime(pathStat.st_mtime);
// 		std::string bytes;
// 		if (S_ISDIR(pathStat.st_mode)) {
// 			name.append("/");
// 			bytes.append("-");
// 		}
// 		else
// 			bytes = formatSize(pathStat.st_size);
// 		appendHtmlRow(path, name, timeStr, bytes, _body);
// 	}
// 	appendHtmlEnd(_body);
// 	closedir(dir);
// }

// int main() 
// {
// 	std::vector<char> _body;
// 	std::string path = "/Users/tmarts/Documents/Projects/webs/webserv";
// 	std::string	requestPath = "/Documets/Projects/webs/webserv";
// 	makeDirectoryListing(path, requestPath, _body);
// 	std::ofstream outf("test.html", std::ios::out | std::ios::trunc);
// 	for (std::vector<char>::iterator it = _body.begin(); it!= _body.end(); ++it) {
// 		outf << *it;
// 	}
	
// }


int main(){

	// const char* getRequest = "P";
	// const char *get2 = "OST http://www.example.com/path/to/resource?query#fragment ";
	// const char *get3 = "H";
	// const char *get4 = "TTP/1.1\r\nhost:localhost\r\nkey key: that and that"
 	// "hallo ballo    \r\n00FALLOyallo: u  \r\nContent-Length: 12  \r";
	// const char *get5 = "\n\r\n123456789112";
	
	// const char *g1 = "POST http://www.example.com/path/to/resource?query#fragment HTTP/1.1";
	// const char *g2 = "\r\nhost:localhost\r\nkey key: that and that";
	// const char *g3 = "hallo ballo    \r\n00FALLOyallo: u  \r\nContent-Length: 18  \r\n";
	// const char *g4 = "\r\n";
	// const char *g7 = "this is body";
	// const char *g5 = "\nt";
	// const char *g6 = "MORE";

	// Request Get;
	// Get.processRequest(getRequest, strlen(getRequest));
	// Get.processRequest(get2, strlen(get2));
	// Get.processRequest(get3, strlen(get3));
	// Get.processRequest(get4, strlen(get4));
	// Get.processRequest(get5, strlen(get5));
	// std::cout << Get<< std::endl;
	// std::cout << "GET Is complete? " << Get.requestComplete() << std::endl << std::endl;
	
	// Request GetChunks;
	// GetChunks.processRequest(g1, strlen(g1));
	// GetChunks.processRequest(g2, strlen(g2));
	// GetChunks.processRequest(g3, strlen(g3));
	// GetChunks.processRequest(g4, strlen(g4));
	// GetChunks.processRequest(g7, strlen(g7));
	// GetChunks.processRequest(g5, strlen(g5));
	// GetChunks.processRequest(g6, strlen(g6));
	// std::cout << GetChunks;
	// std::cout << "Is complete? " << GetChunks.requestComplete() << std::endl << std::endl;

	const char* postRequest =
    "POST /example HTTP/1.1\r\n"
    "Host: example.com\r\n"
	"Something: first instance\r\n"
    "Transfer-Encoding: chunked\r\n"
	"SomeTHING: this44, that   \r\n"
    "\r\n"
  	"A\r\n"
	"Mozilla___\r\n"
	"11\r\n"
	"Developer Network\r\n"
	"0\r\n"
	"\r\n";
	Request Post;
	Post.processRequest(postRequest, strlen(postRequest));
	std::cout << Post;
	std::cout << "Is complete? " << Post.requestComplete() << std::endl<< std::endl;

	const char* p1 =
    "POST /example HTTP/1.1\r\n"
    "Host: example.com\r\n"
	"Something: first instance\r\n"
    "Transfer-Encoding: chunked\r\n"
	"SomeTHING: this44, that   \r\n"
    "\r\n";
  	const char* p2 = "A\r";
	const char* p8 = "\n"
	"Mozilla___\r\n";
	const char* p3 = "11\r\n";
	const char* p5 = "Developer ";
	const char* p6 = "Network";
	const char* p7 = "\r\n";
	const char* p4 ="0\r\n"
	"\r\n";
	Request P;
	P.processRequest(p1, strlen(p1));
	P.processRequest(p2, strlen(p2));
	P.processRequest(p8, strlen(p8));
	P.processRequest(p3, strlen(p3));
	P.processRequest(p5, strlen(p5));
	P.processRequest(p6, strlen(p6));
	P.processRequest(p7, strlen(p7));
	P.processRequest(p4, strlen(p4));
	std::cout << P;
	std::cout << "Is complete? " << P.requestComplete() << std::endl << std::endl;

	// Request Req;
	// const char *line = "GET / HTTP/1.1\r\n\r\n";
	// Req.processRequest(line, strlen(line));
	// std::cout << Req;
	// std::cout << "Is complete? " << Req.requestComplete() << std::endl << std::endl;

}
