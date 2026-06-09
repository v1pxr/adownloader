#include <iostream>
#include <string>
#include <fstream>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

void download(const std::string& url, const std::string& dwnpath){
    std::cout << "downloading " << url << "\n";

    int protocolpos = url.find("://");

    std::string protocol = url.substr(0, protocolpos);

    int hoststart = protocolpos + 3;

    int pathstart = url.find("/", hoststart);

    std::string host = url.substr(hoststart, pathstart - hoststart);

    std::string target = url.substr(pathstart);

    int filenamepos = url.find_last_of("/");
    std::string filename = url.substr(filenamepos + 1);

    if (filename.empty())
    {
        filename = "file";
    }

    std::cout << "protocol = " << protocol << "\n";
    std::cout << "host = " << host << "\n";
    std::cout << "target = " << target << "\n";
    std::cout << "filename = " << filename << "\n";

    try {
        net::io_context ioc;

        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        auto const results = resolver.resolve(host, "80");

        stream.connect(results);

        http::request<http::string_body> req{ http::verb::get, target, 11 };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);


        http::write(stream, req);

        beast::flat_buffer buffer;

        http::response<http::dynamic_body> res;

        http::read(stream, buffer, res);

        if (res.result_int() != 200)
        {
            std::cout << "server code isnt 200: " << res.result_int() << "\n";
            return;
        }

        std::string savepath = dwnpath + "/" + filename;

        std::ofstream out(savepath, std::ios::binary);

        out << beast::buffers_to_string(res.body().data());

        out.close();

        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        if (ec && ec != beast::errc::not_connected)
            throw beast::system_error{ ec };

    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
    return;
}

int main(int argc, char* argv[]){
    if (argc != 4) {
        std::cout << "Not enough parameters\n";
        return 0;
    }

    std::string urlpath = argv[1];
    std::string dwnpath = argv[2];
    int filesnum = std::stoi(argv[3]);

    if (filesnum < 1 || filesnum > 999){
        std::cout << "filesnum out of range\n";
        return 0;
    }

    std::ifstream file(urlpath);

    if (!file.is_open()){
        std::cout << "Cant open urls file\n";
        return 0;
    }

    std::string* urls = new std::string[1000];
    int urlcount = 0;

    std::string line;

    while (std::getline(file, line)){
        urls[urlcount] = line;
        urlcount++;
    }

    for (int i = 0; i < urlcount; i++){
        download(urls[i], dwnpath);
    }

    delete[] urls;
    return 0;
}