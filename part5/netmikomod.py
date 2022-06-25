from netmiko import ConnectHandler

myserver = {
    'device_type': 'linux',
    'host':   '192.168.1.222',  #Your Server IP
    'username': 'c4pt3nn3m0', #your Server Username
    'password': 'qROsBplH0obF', #your server password
    'port' : 8080,
    'secret': '',
}

net_connect = ConnectHandler(**myserver)
net_conenct.enable()
output = net_connect.send_command('uname -a')
print(output)
