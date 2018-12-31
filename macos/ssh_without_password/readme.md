
# SSH 到服务器无需再次输入密码

## 1. 生成 id_rsa.pub

`$ ssh-keygen -t rsa`

然后一直 Enter 即可

## 2. 将 id_rsa.pub 拷贝到服务器上

`$ cat ~/.ssh/id_rsa.pub | ssh [服务器] "mkdir ~/.ssh; cat >> ~/.ssh/authorized_keys"`

然后会让你输入密码

## 3. 完成
