network_debug.h
=======================

クライアントサーバプログラムで使用する構造体の中を可視化するツール．

インストール
-------------------
```
git clone 
```

実行テスト
----------
```
make test
```

使い方
------------------

1. C言語のファイルにincludeする．

```c
#include "network_debug.h"
```

2. 以下の関数が使用可能

- `getaddrinfo(node, service, hints, res)`のうち，resとhintsの各要素を確認（struct addrinfo型)
```
print_getaddrinfo(const struct addrinfo *rp)
```

- `socket(domain,type, protocol)`の引数の中身を確認(protocolは対象外)

```
print_socket_domain(const int domain);
print_socket_type(int type);
```

- `connect(sockfd, addr,addrlen)`の引数のうち，addrの中身を確認

  - IPv4の場合
```
print_sockaddr_in(const struct sockaddr_in *a)
```

  - IPv6の場合
```
print_sockaddr_in6(const struct sockaddr_in6 *a)
```