#include "EchoServerQt4.hpp"
#include "EchoClientQt4.hpp"
#include <QTcpServer>
#include <QTcpSocket>

EchoServerQt4::EchoServerQt4( QObject *parent )
	: QObject( parent ) {
	server_ = new QTcpServer( parent );
}

bool EchoServerQt4::start( const QHostAddress &host, quint16 port ) {
	connect( server_, &QTcpServer::newConnection, this, &EchoServerQt4::onNewConnection );

	return server_->listen( host, port );
}

void EchoServerQt4::onNewConnection() {
	QTcpSocket *socket = server_->nextPendingConnection();
	EchoClientQt4 *client = new EchoClientQt4( this, socket );

	connect( client, &EchoClientQt4::dataReceived, this, &EchoServerQt4::dataReceived );
	connect( client, &EchoClientQt4::dataSent, this, &EchoServerQt4::dataSent );
	connect( client, &EchoClientQt4::disconnected, this, &EchoServerQt4::onDisconnected );

	emit connected( socket );
}

void EchoServerQt4::onDisconnected( EchoClientQt4 *client, QTcpSocket *socket ) {
	emit disconnected( socket );
	client->deleteLater();
	socket->deleteLater();
}
