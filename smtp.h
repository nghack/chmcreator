#ifndef SMTP_H
#define SMTP_H


#include <QtCore>
#include <QCoreApplication>
#include <QObject>

#include <QTcpSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QAbstractSocket>
#include <QDateTime>
#include <QDate>
#include <QLocale>
#include <QObject>
#include <QTcpSocket>
 
/*
      USAGE!
      Smtp *newMail  = new Smtp("remoteserver","username","pass");
      newMail->Send("from@address.com","to@address.com"," Your Subject","My body text");
      class emit ErrorCloseAll() / SuccessQuit()   or get QStringList ErrorMSG; to read error and data....
      
*/







class Smtp : public QObject
{
	Q_OBJECT
    
	public:
		Smtp(QString smtphost, QString smtpusername, QString smtppass);
		~Smtp();
                void setConfig(QString smtphost, QString smtpusername, QString smtppass);
                void send( const QString &from, const QString &to,const QString &subject, const QString &body );
		int linesend;
                QStringList errorMSG;
                QStringList getErrorlist();
	signals:
		void status( const QString &);
                void connectorSuccess();
                void sendLine();
                void errorCloseAll();
                void successQuit();

	private slots:
		void disconnected();
		void connected();
                void readLiner();
                void putSendLine();
	private:
		bool isconnect;
		QString smtphost;
		QString smtpusername;
		QString smtppass;
		QString message;
		QString output;
		QString RemoteServerName;
		QString mailstatus;
		QTextStream *t;
		QTcpSocket *smtpsocket;
		QString from;
		QString rcpt;
		QString response;
                QString sendLineAndGrab(QString senddata);
		int Timeout;
		QString encodeBase64( QString xml );
		QString decodeBase64( QString xml );
		int dateswap(QString form, uint unixtime );
		QString TimeStampMail();
    
 
};








#endif

 



