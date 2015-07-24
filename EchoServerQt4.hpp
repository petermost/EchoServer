#pragma once

#include <QObject>

class QTcpSocket;
class QTcpServer;
class QHostAddress;
class EchoClientQt4;

class EchoServerQt4 : public QObject {
	Q_OBJECT
	public:
		explicit EchoServerQt4( QObject *parent = nullptr );

		bool start( const QHostAddress &, quint16 port );

	signals:
		void connected( QTcpSocket * );
		void disconnected( QTcpSocket * );

		void dataReceived( QTcpSocket *socket, const QByteArray &data );
		void dataSent( QTcpSocket *, qint64 count );

	public slots:

	private:
		void onNewConnection();
		void onDisconnected( EchoClientQt4 *client, QTcpSocket *socket );

		QTcpServer *server_;
};
