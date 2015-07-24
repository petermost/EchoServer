#pragma once

#include <QObject>

class QTcpSocket;
class EchoServerQt4;

class EchoClientQt4 : public QObject {
	Q_OBJECT
	public:
		explicit EchoClientQt4( EchoServerQt4 *serverParent, QTcpSocket *socket );

	signals:
		void dataReceived( QTcpSocket *, const QByteArray & );
		void dataSent( QTcpSocket *, qint64 count );
		void disconnected( EchoClientQt4 *, QTcpSocket * );

	public slots:

	private:
		void onReadyRead();
		void onBytesWritten(qint64 count);
		void onDisconnected();

		EchoServerQt4 *server_;
		QTcpSocket *socket_;
};
