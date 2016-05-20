import dbus, gobject
from dbus.mainloop.glib import DBusGMainLoop


dbus.mainloop.glib.DBusGMainLoop(set_as_default = True)
bus = dbus.SessionBus()

def signal_handler(cipher):
	print cipher

bus.add_signal_receiver(signal_handler, dbus_interface="com.secure.PassGenService")
# bus.add_signal_receiver(signal_handler, dbus_interface="com.canonical.Unity.Panel.Service")

loop=gobject.MainLoop()
loop.run()
