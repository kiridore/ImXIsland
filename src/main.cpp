#include <curl/curl.h>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
// 回调函数，将数据写入 std::string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

// 回调函数，用于处理头部数据
size_t HeaderCallback(char* buffer, size_t size, size_t nitems, void* userdata) {
    size_t total_size = size * nitems;
    std::string header(buffer, total_size);
    
    // 查找 "Content-Type"
    std::string::size_type index = header.find("Content-Type:");
    std::cout << header; // 输出整个 Content-Type 头部
    
    return total_size;
}

int main() {
    CURL* curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        // std::string url = "https://nmb.ovear.info/nmb-notice.json";
        std::string url = "https://api.nmb.best/api/getForumList";
        std::string postData = "";
        std::string response; // 用于保存响应

        // 启用自动解压缩功能
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
        // 设置回调函数和数据缓冲区
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "POST request sent successfully." << std::endl;
            json data = json::parse(response);
            std::cout << data.dump() << std::endl;
        }

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize CURL." << std::endl;
    }

    return 0;
}
