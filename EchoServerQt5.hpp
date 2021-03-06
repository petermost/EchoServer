#pragma once

#include <QObject>

class QTcpSocket;
class QTcpServer;
class QHostAddress;

class EchoServerQt5 : public QObject {
	Q_OBJECT
	public:
		explicit EchoServerQt5( QObject *parent = nullptr );

		bool start( const QHostAddress &, quint16 port );

	signals:
		void connected( QTcpSocket * );
		void disconnected( QTcpSocket * );

		void dataReceived( QTcpSocket *, const QByteArray & );
		void dataSent( QTcpSocket *, qint64 count );

	public slots:

	private:
		void onConnected( QTcpSocket *socket );
		void onDisconnected( QTcpSocket *socket );
		void onReadyRead( QTcpSocket *socket );
		void onBytesWritten( QTcpSocket *socket, qint64 count );

		QTcpServer *server_;
};
