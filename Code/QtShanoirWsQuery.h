/*
 * QtShanoirWsQuery.h
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
 */

#ifndef QTSHANOIRWSQUERY_H_
#define QTSHANOIRWSQUERY_H_

#include <QtCore>

class QtShanoirWsQuery : public QObject
{
    Q_OBJECT
    public:
        QtShanoirWsQuery(): displayResult(false) {}
        QtShanoirWsQuery(QString ws) : WebService(ws), displayResult(false) {}
        QtShanoirWsQuery(QString ws, QString im) : WebService(ws), WsImpl(im), displayResult(false) {}

        QString WebService;
        QString WsImpl; // WebService implementation
        bool displayResult;

        QString WsMethod;
        QList<QPair<QString, QString> > WsMethodarg;

        void
        answer(QString string) const;
    signals:
        void
        response(QString string) const;
};

#endif /* QTSHANOIRWSQUERY_H_ */
