# 1. 配置ssh

    sudo apt update
    sudo apt install openssh-server gcc g++ gdb make cmake git net-tools

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




检查内核版本  uname -r