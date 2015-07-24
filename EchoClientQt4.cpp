#include "EchoClientQt4.hpp"
#include "EchoServerQt4.hpp"
#include <QTcpSocket>

EchoClientQt4::EchoClientQt4( EchoServerQt4 *serverParent, QTcpSocket *socket )
	: QObject( serverParent ), server_( serverParent ), socket_( socket ) {

	connect( socket_, &QTcpSocket::readyRead, this, &EchoClientQt4::onReadyRead );
	connect( socket_, &QTcpSocket::bytesWritten, this, &EchoClientQt4::onBytesWritten );
	connect( socket_, &QTcpSocket::disconnected, this, &EchoClientQt4::onDisconnected );
}

void EchoClientQt4::onReadyRead() {
	QByteArray data = socket_->readAll();
	emit dataReceived( socket_, data );
}

void EchoClientQt4::onBytesWritten( qint64 count ) {
	emit dataSent( socket_, count );
}

void EchoClientQt4::onDisconnected() {
	emit disconnected( this, socket_ );
}
