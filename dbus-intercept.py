def handler( message):
	print message

import dbus, gobject
from dbus.mainloop.glib import DBusGMainLoop
dbus.mainloop.glib.DBusGMainLoop(set_as_default = True)
bus = dbus.SessionBus()

bus.add_signal_receiver(handler, dbus_interface="com.secure.PassGenService")

loop=gobject.MainLoop()
loop.run()