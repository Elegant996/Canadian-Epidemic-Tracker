//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : E-Healthcare-Canada
//  @ File Name : Trackables.h
//  @ Date : 11/9/2010
//  @ Author : 
//
//


#if !defined(_TRACKABLES_H)
#define _TRACKABLES_H

#include <QString>
#include "City.h"
#include <QDate>

class Trackables
{
protected:
	int ID;
	int Type;
	int Quantity;
        float longitude;
        float latitude;
        QDate theDate;

public:
        Trackables( int id = 0, int type = 0, int quantity = 0, float lon = 0,float lat=0, QDate = QDate::currentDate());
        virtual ~Trackables();
        virtual int getID() = 0;
        int getType();
        int getQuantity();

        void setType(int);
        void setQuantity(int);

        float getLon();
        void  setLon(float newLon);
        float getLat();
        void  setLat(float newLat);

        QDate getDate();
        void setDate(QDate date);


};

#endif  //_TRACKABLES_H