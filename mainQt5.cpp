#include <QCoreApplication>
#include "EchoServerQt5.hpp"
#include <QHostAddress>
#include <QTcpSocket>

const quint16 PORT = 55000;

QTextStream out( stdout );

QTextStream &operator << ( QTextStream &stream, const QTcpSocket &socket ) {
	QString peerName = socket.peerName();
	return stream << peerName << ":" << socket.peerPort();
}

int main(int argc, char *argv[]) {

	QCoreApplication application(argc, argv);

	EchoServerQt5 *echoServer = new EchoServerQt5( &application );

	// Handle the connected signal:

	QObject::connect( echoServer, &EchoServerQt5::connected, []( QTcpSocket *socket ) {
		out << "Accepted connection from " << *socket << endl;
	});

	// Handle the disconnected signal:

	QObject::connect( echoServer, &EchoServerQt5::disconnected, []( QTcpSocket *socket ) {
		out << "Disconnected from " << *socket << endl;
	});

	// Handle the received data:

	QObject::connect( echoServer, EchoServerQt5::dataReceived, []( QTcpSocket *socket, const QByteArray &data ) {
		out << "Received data from " << *socket << ": " << data << endl;
	});

	// Handle that data has been sent:

	QObject::connect( echoServer, EchoServerQt5::dataSent, []( QTcpSocket *socket, qint64 count ) {
		out << "Sent data to " << *socket << ": " << count << endl;
	});

	echoServer->start( QHostAddress::Any, PORT );

	return application.exec();
}
