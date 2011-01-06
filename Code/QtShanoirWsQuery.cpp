/*
 * QtShanoirWsQuery.cpp
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
 */

#include <QtShanoirWsQuery.h>

void
QtShanoirWsQuery::answer(QString str)
{
    emit response(str);
}
