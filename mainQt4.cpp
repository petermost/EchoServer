#include <QCoreApplication>
#include "EchoServerQt4.hpp"
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

	EchoServerQt4 *echoServer = new EchoServerQt4( &application );
	QObject::connect( echoServer, &EchoServerQt4::connected, []( QTcpSocket *socket ) {
		out << "Accepted connection from " << *socket << endl;
	});

	QObject::connect( echoServer, &EchoServerQt4::disconnected, []( QTcpSocket *socket ) {
		out << "Disconnected from " << *socket << endl;
	});

	QObject::connect( echoServer, EchoServerQt4::dataReceived, []( QTcpSocket *socket, const QByteArray &data ) {
		out << "Received data from " << *socket << ": " << data << endl;
	});

	QObject::connect( echoServer, EchoServerQt4::dataSent, []( QTcpSocket *socket, qint64 count ) {
		out << "Sent data to " << *socket << ": " << count << endl;
	});

	echoServer->start( QHostAddress::Any, PORT );

	return application.exec();
}
