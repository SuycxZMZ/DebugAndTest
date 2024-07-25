# 1. 配置ssh

    sudo apt update
    sudo apt install build-essential
    sudo apt install openssh-server gdb cmake git net-tools linux-tools-generic


确认SSH服务正在运行
    sudo systemctl status ssh

如果SSH服务没有自动启动，可以手动启动它
    sudo systemctl start ssh

确保SSH服务设置为开机启动
    sudo systemctl enable ssh

配置防火墙允许SSH连接（默认端口22）
    sudo ufw allow ssh


# 免密码登陆

windows 生成公钥
    ssh-keygen # 一直回车到密钥生成，生成私钥id_rsa和公钥id_rsa.pub

在ubuntu端记录公钥信息
    cd 
    ls -a

应该会有 .ssh 文件夹，没有的话就创建一个
    sudo vim ~/.ssh/authorized_keys

如果authorized_keys里有内容，则在最后重起一行粘贴公钥；
如果没有内容则直接粘贴，编辑完成后要分别设置文件夹和文件权限：
    chmod 700 ~/.ssh
    chmod 600 ~/.ssh/authorized_keys

在vscode的config中，在要登录的Host最后加上私钥认证：
    IdentityFile C:\Users\用户名\.ssh\id_rsa


检查内核版本  uname -r
apt安装的包卸载 
    sudo apt-get remove 软件包名
    sudo apt-get autoremove

后台运行程序，比如redis
    sudo systemctl start redis
    sudo systemctl stop redis