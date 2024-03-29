#include "../../include/webserv.hpp"

Server::Server() : port(0), root(), clientSize(0), clientBody(0), autoindex(true), socketFd(-1), connectedClients(0) {
	inet_aton(DEFAULT_ADDRESS, &this->host);
}

Server::Server(const Server &server) : port(server.port), host(server.host),
									   serverName(server.serverName), root(server.root), index(server.index),
									   ipAddress(server.ipAddress), clientSize(server.clientSize), clientBody(server.clientBody),
									   errorPages(server.errorPages),locations(server.locations), autoindex(server.autoindex),
									   cgi_info(server.cgi_info), redirect(server.redirect),socketFd(server.socketFd),
									   connectedClients(server.connectedClients){
	return;
}

Server &Server::operator=(const Server &server) {
	if (&server != this)
	{
		this->port = server.port;
		this->host = server.host;
		this->serverName = server.serverName;
		this->root = server.root;
		this->index = server.index;
		this->ipAddress = server.ipAddress;
		this->clientSize = server.clientSize;
		this->clientBody = server.clientBody;
		this->errorPages = server.errorPages;
		this->autoindex = server.autoindex;
		this->cgi_info = server.cgi_info;
		this->redirect = server.redirect;
		this->socketFd = server.socketFd;
		this->connectedClients = server.connectedClients;
	}
	return *this;
}

Server::~Server() {}

void Server::setPort(unsigned short port) {
	if (this->port)
		throw std::runtime_error("Config file error: server's port was initialized twice.");
	this->port = port;
}

void Server::setHost(std::string host) {
	if (strcmp(inet_ntoa(this->host), DEFAULT_ADDRESS))
		throw std::runtime_error("Config file error: server's host was initialized twice.");
	if (!inet_aton(host.c_str(), &this->host))
		throw std::runtime_error("Config file error: invalid host name.");
}

void Server::setName(std::string name) {
	serverName.push_back(name);
}

void Server::setRoot(std::string root) {
	if (!this->root.empty()){
		throw std::runtime_error("Config file error: root was set twice.");
	}
	struct stat sb;

	if (stat(root.c_str(), &sb) == 0)
		this->root = root;
	else
		throw std::runtime_error("Config file error: root directory does not exist.");
}

void Server::setIndex(std::string index) {
	this->index.push_back(index);
}

void Server::setIP() {
	if (!strcmp(inet_ntoa(this->host), DEFAULT_ADDRESS) || !port || root.empty())
		throw std::runtime_error("Config file error: server input incomplete.");
	this->ipAddress = inet_ntoa(this->host);
	this->ipAddress += ":";
	std::stringstream ss;
	ss << this->port;
	this->ipAddress += ss.str();
}

void Server::setClientSize(unsigned long clientSize) {
	if (!clientSize)
		throw std::runtime_error("Config file error: client size can't be 0.");
	if (this->clientSize)
		throw std::runtime_error("Config file error: client size was initialized twice.");
	this->clientSize = clientSize;
}

void Server::setClientBody(unsigned long clientBody) {
	if (!clientBody)
		throw std::runtime_error("Config file error: client body size can't be 0.");
	if (this->clientBody)
		throw std::runtime_error("Config file error: client body size was initialized twice.");
	this->clientBody = clientBody;
}

void Server::setDefaultClientSize() {
	if (!clientSize) {
		clientSize = DEFAULT_CLIENT_SIZE;
	}
	if (!clientBody) {
		clientBody = DEFAULT_CLIENT_BODY_SIZE;
	}
}

void Server::setErrorPage(int key, std::string errorPage) {
	if (key > 511 || key < 400)
		throw std::runtime_error("Config file error: error codes from 400 to 511.");
	this->errorPages.insert(std::make_pair(key, errorPage));
}

void Server::setAutoIndex(std::string autoindex) {
	if (autoindex == "true"){
		this->autoindex = true;
	}
	else if (autoindex == "false"){
		this->autoindex = false;
	}
	else
		throw std::runtime_error("Config file error: autoindex can only be set to true or false.");
}

void Server::setCgiInfo(std::string info) {
	this->cgi_info.push_back(info);
}

void Server::setRedirect(std::string redirect) {
	if (!this->redirect.empty())
		throw std::runtime_error("Config file error: Can only have one redirection per location.");
	this->redirect = redirect;
}

/* ************************************************************************** */
/*                                  GETTERS                                   */
/* ************************************************************************** */

std::string Server::getRoot() const {
	return (this->root);
}

std::string Server::getServerName() const {
	if (this->serverName.empty()) {
		return (SERVER_VERSION);
	}
	return (this->serverName.back());
}

unsigned short Server::getPort() const {
	return (this->port);
}

const std::string &Server::getIpAddr() const{
	return (this->ipAddress);
}

std::vector<std::string> Server::getIndex() const{
	return (this->index);
}

bool Server::isAutoIndex() const {
	return this->autoindex;
}

std::vector <std::string> Server::getCgiInfo() const {
	return this->cgi_info;
}

int Server::getSocketFd() const {
	return this->socketFd;
}

void Server::setSocketFd(int socketFd) {
    this->socketFd = socketFd;
}

Location Server::getLocation(const std::string &path) const {
	std::string dir = path.substr(0, path.rfind("/"));
	std::map<std::string, Location>::const_iterator it;
	while (!dir.empty()) {
		if ((it = locations.find(dir)) != locations.end()) {
			return (it->second);
		}
		dir.erase(dir.rfind("/"));
	}
	if ((it = locations.find("/")) != locations.end()) {
		return (it->second);
	}

	Location location;
	location.autoCompleteFromServer(*this);
	return location;
}

void Server::autoCompleteLocations() {
	for (std::map<std::string, Location>::iterator it = this->locations.begin(); it != this->locations.end(); it++) {
		it->second.autoCompleteFromServer(*this);
	}
}

std::string Server::getErrorPage(int status) const {
	std::map<int, std::string>::const_iterator it = errorPages.find(status);
	if (it == errorPages.end()) {
		return ("");
	}
	return (it->second);
}

unsigned long Server::getClientBodySize() const {
	return this->clientBody;
}

std::vector<std::string>    &Server::getServerNames() {
    return this->serverName;
}

std::string Server::getRedirect() const{
	return this->redirect;
}

bool Server::hasServerName(std::vector<std::string> &serverName) const {
    for (std::vector<std::string>::iterator it = serverName.begin(); it != serverName.end(); ++it) {
        if (std::find(this->serverName.begin(), this->serverName.end(), *it) != this->serverName.end()) {
            return (true);
        }
    }
    return (false);
}
