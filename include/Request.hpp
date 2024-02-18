#pragma once

#include "utils.hpp"

enum ParseState {
	stateParseRequestLine,
	stateParseHeaders,
	stateCheckBody,
	stateParseMessageBody,
	stateParseChunkedBody,
	requestParseFAIL, //indicates falure of parser as opposed to problem with request
	requestERROR, // indicates a problem in the request
	requestOK,
};

enum RequestLineState {
	stateParseMethod,
	stateParseUri,
	stateParseHTTPver,
	requestLineOK,
};

// REQUEST CLASS provides functions to parse the request and save the Request data. 
class Request
{
private:
	ParseState			state_;
	RequestLineState	rlstate_;

	std::string			methodStr_;
	RequestMethod		method_;
	std::string			uri_; //can be either abs URI or abs path. We don't handle '*' or authority
	std::string         path_; //is absolute path in relation to the root or location of the server, extracted from URI
	std::string     	query_;
	std::string         fragment_;
	std::string			httpVer_;

	std::map<std::string, std::string> headers_;
	std::vector<char> 	body_;

	int					statusCode_; //is 0 if no problem is found
	std::string			errorMsg_; //mostly for debugging to get the precise source of error

	Request(const Request& rhs);
	Request &operator=(const Request& rhs);

	const char *extractHeadersStream(std::stringstream& headersStream, const char *requestBuf, const char *msgEnd);
	
	void		parseRequestLine(std::stringstream& headersStream);
	void		parseMethod(std::stringstream& requestLine);
	void		parseURI(std::stringstream& requestLine);
	void		parseHTTPver(std::stringstream& requestLine);

	void		parseHeader(std::stringstream& headersStream);
	void		checkForBody(const char *bodyStart, const char *msgEnd);
	void		storeBody(const char *bodyStart, const char *msgEnd);
	const char 	*decodeChunked(const char *chunkStart, const char *msgEnd);

	void 		setError(ParseState type, int errorCode, const char *message);
	void		clearRequest();
	
	std::string& trimString(std::string& str);
	bool 		containsControlChar(std::string& str) const;

public:
	Request();
	~Request();

	void				processRequest(const char* requestBuf, int messageLen);

	const RequestMethod& getMethod() const;
	const std::string&	getUri() const;
	const std::string& 	getHttpVer() const;
	const std::string&	getPath() const;
	const std::string&	getQuery() const;
	const std::string&  getFragment() const;
	const int&			getErrorCode() const;
	const std::string&	getErrorMsg() const;
	std::string			getHeaderValueForKey(const std::string& key) const;
    const std::vector<char>& getBody() const;

	std::map<std::string, std::string>::const_iterator	getHeadersBegin() const;
	std::map<std::string, std::string>::const_iterator	getHeadersEnd() const;
	std::vector<char>::const_iterator					getBodyBegin() const;
	std::vector<char>::const_iterator					getBodyEnd() const;

	bool				isTransferEncodingChunked() const;
	bool 				isConnectionClose() const;
};

std::ostream& operator<<(std::ostream& out, const Request& rhs);