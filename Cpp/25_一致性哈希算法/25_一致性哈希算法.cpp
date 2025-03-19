/**
 * @file 25_一致性哈希算法.cpp
 * @author vurtnewk
 * @brief
 */

#include <iostream>
#include <list>
#include <map>
#include <set>
// 这 vscode 里，为了快捷键能直接运行，所以直接包含的cpp
#include "md5.cpp"

#if 0
int main() {
    // MD5
    cout << MD5("hello world") << endl;
    cout << getMD5("110") << endl;
    cout << getMD5("111") << endl;
    cout << getMD5("192.168.1.100#0") << endl;
    cout << getMD5("192.168.1.100#1") << endl;
}
#endif

// 一致性哈希环的取值类型
using unit = unsigned int;

using namespace std;
// 前置生命物理节点主机类型
class PhscialHost;

// 虚拟节点
class VirtualHost {
   public:
    VirtualHost(string ip, PhscialHost* p) : ip_(ip), phscialHost_(p) { md5_ = ::getMD5(ip_.c_str()); }
    // 重载函数
    bool operator<(const VirtualHost& host) const { return md5_ < host.md5_; }
    bool operator==(const VirtualHost& host) const { return ip_ == host.ip_; }

    uint getMD5() const { return md5_; }
    const PhscialHost* getPhscialHost() const { return phscialHost_; }

   private:
    string ip_;                 // 虚拟节点的ip信息
    uint md5_;                  // 虚拟节点在一致性哈希环上的位置
    PhscialHost* phscialHost_;  // 虚拟节点隶属的物理节点
};

// 物理节点
class PhscialHost {
   public:
    PhscialHost(string ip, int vnumber) : ip_(ip) {
        for (int i = 0; i < vnumber; i++) {
            virtualHosts_.emplace_back(ip + "#" + ::to_string(i), this);
        }
    }

    string getIP() const { return ip_; }
    // 返回的是 virtualHosts_ 的 const 引用 ，不会创建拷贝
    const list<VirtualHost>& getVirtualHosts() const { return virtualHosts_; }

   private:
    string ip_;                       // 物理机器的ip地址
    list<VirtualHost> virtualHosts_;  // 存储虚拟节点列表
};

// 一致性哈希算法代码实现
class ConsistentHash {
   public:
    // 在一致性哈希环上添加物理主机的虚拟节点
    void addHost(PhscialHost& host) {
        // 获取物理主机所有的虚拟节点列表
        auto list = host.getVirtualHosts();
        for (auto host : list) {
            hashCircle_.insert(host);
        }
    }
    // 在一致性哈希环上删除物理主机的虚拟节点
    void delHost(PhscialHost& host) {
        // 获取物理主机所有的虚拟节点列表
        auto list = host.getVirtualHosts();
        for (auto host : list) {
            auto it = hashCircle_.find(host);
            if (it != hashCircle_.end()) {
                // 在一致性哈希环上删除所有物理主机对应的虚拟节点
                hashCircle_.erase(it);
            }
        }
    }
    // 返回负载的真实物理主机的ip信息
    string getHost(string clientip) const {
        uint md5 = getMD5(clientip.c_str());
        for (auto vhost : hashCircle_) {
            if (vhost.getMD5() > md5) {
                return vhost.getPhscialHost()->getIP();
            }
        }
        // 映射从0开始遇见的第一个虚拟节点
        return hashCircle_.begin()->getPhscialHost()->getIP();
    }

   private:
    // 等于java 中的 TreeSet ， 是红黑树实现
    set<VirtualHost> hashCircle_;  // 一致性哈希环
};

void ShowConsistentHash(ConsistentHash& chash) {
    list<string> iplists{"192.168.1.123", "192.168.1.12", "192.168.1.13", "192.168.1.23", "192.168.1.54",
                         "192.168.1.89",  "192.168.1.21", "192.168.1.27", "192.168.1.49", "192.168.1.145",
                         "192.168.2.34",  "192.168.6.78", "192.168.2.90", "192.168.4.5"};

    map<string, list<string>> logMap;

    for (auto clientip : iplists) {
        // 返回负载的真实物理主机的ip信息
        string host = chash.getHost(clientip);
        logMap[host].emplace_back(clientip);
    }

    for (auto pair : logMap) {
        cout << "物理主机:" << pair.first << endl;
        cout << "客户端映射的数量:" << pair.second.size() << endl;

        for (auto ip : pair.second) {
            cout << ip << endl;
        }

        cout << "----------------------------" << endl;
    }
    cout << endl;
}

// 测试一致性哈希算法的功能
int main() {
    PhscialHost host1("10.117.124.10", 150);
    PhscialHost host2("10.117.124.20", 150);
    PhscialHost host3("10.117.124.30", 150);

    ConsistentHash chash;
    chash.addHost(host1);
    chash.addHost(host2);
    chash.addHost(host3);

    ShowConsistentHash(chash);

    // 模拟host1有故障
    chash.delHost(host1);

    ShowConsistentHash(chash);
}