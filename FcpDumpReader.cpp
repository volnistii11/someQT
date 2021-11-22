#include "FcpDumpReader.h"

#include <QCoreApplication>
#include <QRegularExpression>
#include <QDebug>
#include <stdio.h>

#include <QString>



FcpDumpReader::FcpDumpReader()
{

}

void FcpDumpReader::ReadDump()
{
    QString str = "dbCreateCellBoundary _cell '((0.000 0.000) (9089.000 0.000) (9089.000 9000.000) (0.000 9000.000) (0.000 0.000))";
    QRegularExpression boundary("^[[:blank:]]*dbCreateCellBoundary");
    QRegularExpressionMatch match = boundary.match(str);

    if (match.hasMatch()) {
        QRegularExpression real("[-+]?[0-9]*[.,][0-9]+(?:[eE][-+]?[0-9]+)?");
        QRegularExpressionMatchIterator i = real.globalMatch(str);

        int x_or_y = 0;
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            QString coordinate = match.captured(0);
            if (x_or_y%2 == 0){
                printf("x: %s\n",coordinate.toUtf8().data());
            }
            else {
                printf("y: %s\n",coordinate.toUtf8().data());
            }
            x_or_y++;
        }
    }
}
