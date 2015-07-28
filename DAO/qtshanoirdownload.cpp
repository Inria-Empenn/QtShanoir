#include "qtshanoirdownload.h"

QtShanoirDownload::QtShanoirDownload()
{


}
void QtShanoirDownload::getFileName(QString xmlserializer)
{
    qDebug()<<"xmlserializer"<<xmlserializer;
    QDomDocument doc;
    doc.setContent (xmlserializer);
    QDomNode n = doc.firstChild().firstChild().nextSibling().firstChild().firstChild();
    if (n.isElement())
    {
        qDebug()<<"DownloadFileNametoElement"<<n.toElement().text();
        setDownloadFileName(n.toElement().text());
    }
    qDebug()<<"DownloadFileName"<<getDownloadFileName();
}

void QtShanoirDownload::downloadDataset(QByteArray bin, QString datasetId, QString downloadDirectory)
{
    int id = datasetId.toInt();
    if (bin.isEmpty())
    {
        //emit queryFailed("Empty binary");
        qDebug()<<"Empty binary";
        //return;
    }

    QString tmpName = downloadFileName.isEmpty() ? QString ( "%1.nii.gz" ).arg (id) : downloadFileName;
    tmpName.replace ( QDir::separator(),"_" );
    QFile dFile (downloadDirectory + QDir::separator() + tmpName);

    dFile.open (QFile::WriteOnly);
    dFile.write (bin);
    dFile.close();

    //download metadata
    QString metadataFileName = "";
//    if (downloadMetadata)
//    {
//        this->downloadMetadata ( datasetId );
//        metadataFileName = dFile.fileName().replace ( ".nii.gz", ".xml" ).replace ( ".nii", ".xml" ).replace ( ".zip", ".xml" );
//    }

    if (dFile.fileName().contains (".zip"))
    {
        // Decompression using QuaZIP
        QuaZip zipFile (dFile.fileName());
        zipFile.open (QuaZip::mdUnzip);
        QuaZipFileInfo info;
        QuaZipFile file (&zipFile);

        for (bool more = zipFile.goToFirstFile(); more; more = zipFile.goToNextFile())
        {
            zipFile.getCurrentFileInfo ( &info );
            file.open ( QIODevice::ReadOnly );
            QString name = file.getActualFileName();
            QString outFileName = downloadDirectory + QDir::separator() + name;
            QFile out (outFileName);
            out.open (QIODevice::WriteOnly);

            char buf[4096];
            char c;
            int len = 0;
            while (file.getChar(&c))
            {
                buf[len++] = c;
                if (len >= 4096)
                {
                    out.write (buf, len);
                    len = 0;
                }
            }
            if (len > 0)
            {
                out.write (buf, len);
            }
            out.close();
//            if (name.contains (".nii") || name.contains (".nii.gz"))
//                emit downloadFinished (outFileName, metadataFileName);
            file.close();
        }
        zipFile.close();
    }
    //else
        //emit downloadFinished (dFile.fileName(), metadataFileName);

}

QString QtShanoirDownload::getDownloadFileName()
{
    return this->downloadFileName;
}

void QtShanoirDownload::setDownloadFileName(QString name)
{
    this->downloadFileName = name;
}
