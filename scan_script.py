import serial
import matplotlib.pyplot as plt

def handleScan():
	xs = []
	ys = []
	zs = []
	i = 0
	ser.write( b'h' )
	print( ser.readline() )
	curline = ser.readline()
	while( curline is not "END" ):
		[ x, y, z ] = curline.split("\t")
		xs[ i ] = x
		ys[ i ] = y
		zs[ i ] = z
		i = i + 1
		curline = ser.readline()
	return ( xs, ys, zs )


if __name__ == "__main__":
	ser = serial.Serial();
	ser.baudrate = 9600
	while( not ser.is_open ):
		ser.port = input( "Enter port name for scanner device: " )
		ser.open()
		if( not ser.is_open ):
			print( "Cannot open serial port... try again" )
	input( "Press enter to begin scan..." )
	fig = plt.figure()
	ax = fig.add_subplot( 111, projection = '3d' )
	( xs, ys, zs ) = handleScan()
	ax.scatter( xs, ys, zs )
	ax.set_xlabel( "X Axis" )
	ax.set_ylabel( "Y Axis" )
	ax.set_zlabel( "Z Axis" )
	plt.show()
