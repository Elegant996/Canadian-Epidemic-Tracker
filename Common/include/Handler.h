#ifndef Handler_H
#define Handler_H

#include <QtXml/QXmlDefaultHandler>
#include <QStack>

#include "../ReplyObjectHeaders/reply.h"
#include "../ReplyObjectHeaders/loginmsg.h"
#include "../ReplyObjectHeaders/loginreply.h"
#include "../ReplyObjectHeaders/logoutreply.h"
#include "../ReplyObjectHeaders/readupdate.h"
#include "../ReplyObjectHeaders/updatereply.h"
#include "../ReplyObjectHeaders/logoutmsg.h"
#include "../ReplyObjectHeaders/writeupdate.h"
#include "../ReplyObjectHeaders/readupdatereply.h"
#include "../ReplyObjectHeaders/writeupdatereply.h"
#include "../ReplyObjectHeaders/newrevisionmsg.h"
#include "../ReplyObjectHeaders/messageerror.h"

class Handler : public QXmlDefaultHandler{
public:
    Handler();
    ~Handler();

    Reply* getReply();
    UpdateReply* getUpdate();
    bool startElement(const QString &, const QString &, const QString &name, const QXmlAttributes &attrs);
    bool characters(const QString &ch);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    bool fatalError(const QXmlParseException &exception);
    bool endDocument();
    bool startDocument();
    bool error(const QXmlParseException &exception);

private:
   void clean();
   UpdateReply* update;
   QString msgType;
   Reply* theReply;
   QStack<QString> theStack;
   QString string1;
   QString string2;
   QString errormsg;
   float lat;
   float lng;
   float latDest;
   float lngDest;
   QDate theDate;
   QDate created;
   QDate sent;
   QDate expected;
   int x;
   bool isShipmentDest;
   bool expectedDate;
   bool createdDate;
   bool sentDate;
   bool received;

};

#endif // Handler_H
