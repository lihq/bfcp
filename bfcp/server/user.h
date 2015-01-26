#ifndef BFCP_USER_H
#define BFCP_USER_H

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <muduo/net/InetAddress.h>
#include <bfcp/common/bfcp_param.h>

namespace bfcp
{

class User : boost::noncopyable
{
public:
  User(uint16_t userID, const string &displayName, const string &uri)
      : userID_(userID),
        displayName_(displayName),
        uri_(uri),
        isAvailable_(false)
  {}

  uint16_t getUserID() const { return userID_; }
  
  void setDisplayName(const string &displayName) { displayName_ = displayName; }
  const string& getDisplayName() const { return displayName_; }
  
  void setURI(const string &uri) { uri_ = uri; }
  const string& getURI() const { return uri_; }

  void setAvailable(bool available) { isAvailable_ = available; }
  bool isAvailable() const { return isAvailable_; }

  void setAddr(const muduo::net::InetAddress &addr) { addr_ = addr; }
  const muduo::net::InetAddress& getAddr() const { return addr_; }

  bool increaseFloorRequestCountOfAFloor(uint16_t floorID, uint16_t maxFloorRequestCount);
  void decreaseFloorRequestCountOfAFloor(uint16_t floorID);
  uint16_t getFloorRequestCountOfAFloor(uint16_t floorID) const;
  void clearFloorRequestCountOfAFloor(uint16_t floorID);
  void clearAllFloorRequestCount() { floorRequestCounter_.clear(); }

  UserInfoParam toUserInfoParam() const 
  {
    UserInfoParam param;
    param.id = userID_;
    param.username = displayName_;
    param.useruri = uri_;
  }

private:
  // key: floor ID, value: request count
  typedef std::map<uint16_t, uint16_t> FloorRequestMap;

  uint16_t userID_;
  string displayName_;
  string uri_;
  muduo::net::InetAddress addr_;
  FloorRequestMap floorRequestCounter_;
  bool isAvailable_;
};

typedef boost::shared_ptr<User> BfcpUserPtr;

} // namespace bfcp

#endif // BFCP_USER_H