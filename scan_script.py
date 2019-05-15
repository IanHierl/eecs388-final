from mpl_toolkits.mplot3d import Axes3D
import serial
import matplotlib.pyplot as plt

def getLineAsStr():
	return str( ser.readline(), "utf-8" ).replace( "\r\n", "" )

def handleScan():
	xs = []
	ys = []
	zs = []
	ser.write( b'h' )
	print( getLineAsStr() )
	print( getLineAsStr() )
	curline = getLineAsStr()
	while( True ):
		print( curline )
		if( "END" in curline ):
			break
		[ x, y, z ] = curline.split("\t")
		[ x, y, z ] = [ int(x), int(y), int(z) ]
		xs.append( x )
		ys.append( y )
		zs.append( z )
		curline = getLineAsStr()
	return [ xs, ys, zs ]


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
	ax = Axes3D( fig )
	[ xs, ys, zs ] = handleScan()
	ser.close()
	ax.scatter( xs, ys, zs )
	ax.set_xlabel( "X Axis" )
	ax.set_ylabel( "Y Axis" )
	ax.set_zlabel( "Z Axis" )
	input( "Data plotted. Press enter to display..." )
	plt.show()
