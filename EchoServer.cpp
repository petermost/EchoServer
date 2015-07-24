#include "EchoServer.hpp"
#include <QTcpServer>
#include <QTcpSocket>

EchoServer::EchoServer( QObject *parent )
	: QObject( parent ) {
	server_ = new QTcpServer( parent );
}

bool EchoServer::start( const QHostAddress &host, quint16 port ) {
	connect( server_, &QTcpServer::newConnection, [ = ] {
		onConnected( server_->nextPendingConnection() );
	});
	return server_->listen( host, port );
}

void EchoServer::onConnected( QTcpSocket *socket ) {
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

void EchoServer::onReadyRead( QTcpSocket *socket ) {
	QByteArray data = socket->readAll();
	emit dataReceived( socket, data );
	socket->write( data );

}

void EchoServer::onBytesWritten( QTcpSocket *socket, qint64 count ) {
	emit dataSent( socket, count );
}

void EchoServer::onDisconnected( QTcpSocket *socket ) {
	emit clientDisconnected( socket );
	socket->deleteLater();
}
