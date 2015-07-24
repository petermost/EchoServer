#include "EchoServerQt5.hpp"
#include <QTcpServer>
#include <QTcpSocket>

EchoServerQt5::EchoServerQt5( QObject *parent )
	: QObject( parent ) {
	server_ = new QTcpServer( parent );
}

bool EchoServerQt5::start( const QHostAddress &host, quint16 port ) {
	connect( server_, &QTcpServer::newConnection, [ = ] {
		onConnected( server_->nextPendingConnection() );
	});
	return server_->listen( host, port );
}

void EchoServerQt5::onConnected( QTcpSocket *socket ) {
	Q_ASSERT( socket != nullptr );
	emit clientConnected( socket );

	connect( socket, &QTcpSocket::readyRead, [ = ] {
		onReadyRead( socket );
	});

	connect( socket, &QTcpSocket::bytesWritten, [ = ]( qint64 count ) {
		onBytesWritten( socket, count );
	});

	connect( socket, &QTcpSocket::disconnected, [ = ] {
		onDisconnected( socket );
	});
}

void EchoServerQt5::onReadyRead( QTcpSocket *socket ) {
	QByteArray data = socket->readAll();
	emit dataReceived( socket, data );
	socket->write( data );

}

void EchoServerQt5::onBytesWritten( QTcpSocket *socket, qint64 count ) {
	emit dataSent( socket, count );
}

void EchoServerQt5::onDisconnected( QTcpSocket *socket ) {
	emit clientDisconnected( socket );
	socket->deleteLater();
}
