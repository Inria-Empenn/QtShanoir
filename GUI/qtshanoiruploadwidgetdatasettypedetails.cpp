#include "qtshanoiruploadwidgetdatasettypedetails.h"

QtShanoirUploadWidgetDatasetTypeDetails::QtShanoirUploadWidgetDatasetTypeDetails(QWidget *parent):QWizardPage(parent),ui (new Ui::QtShanoirUploadWidgetDatasetTypeDetails)
{
    ui->setupUi(this);
    setButtonText(QWizard::FinishButton,tr("Upload"));
    setButtonText(QWizard::BackButton,tr("< Back"));
    setButtonText(QWizard::CancelButton,tr("Cancel"));

    attachShowStepsWidget(ui->steps);

    //Explain step
    ui->detailsLabel->setText(tr("<b> Step 6 : </b> Complete missed information related to each processed dataset."));
    initConnections();
}

void QtShanoirUploadWidgetDatasetTypeDetails::initConnections()
{
    connect(ui->datasetTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(showWidget(QString)));
    connect(this, SIGNAL(callBuildUpdateSteps(QMap<QString, int>)), showsteps, SLOT(buildUpdateSteps(QMap<QString, int>)));
}

void QtShanoirUploadWidgetDatasetTypeDetails::updateDatasetTypeSelectedList(QStringList list)
{
    this->datasetTypeSelectedList = list;
    fillComboBox();
}

void QtShanoirUploadWidgetDatasetTypeDetails::updateShowStepsList()
{
    if (!datasetTypeSelectedList.isEmpty())
    {
        showStepsList.clear();
        for(int i=0; i<datasetTypeSelectedList.size();i++)
        {
            QString datasetType = datasetTypeSelectedList.value(i);
            if(datasetType == "MrDataset")
            {
                if(validationMrDatasetWithoutErrorMessage())
                    showStepsList.insert(datasetType,1);
                else
                    showStepsList.insert(datasetType,0);

            }
            else if(datasetType == "MrSpectroscopyDataset")
            {
                if(validationMrSpectroscopyDatasetWithoutErrorMessage())
                    showStepsList.insert(datasetType,1);
                else
                    showStepsList.insert(datasetType,0);
            }
            else if(datasetType == "CalibrationDataset")
            {
                if(validationCalibrationDatasetWithoutErrorMessage())
                    showStepsList.insert(datasetType,1);
                else
                    showStepsList.insert(datasetType,0);
            }
            else if((datasetType == "EegDataset") || (datasetType == "MegDataset") || (datasetType == "PetDataset"))
            {
                if(validationEegMegPetDatasetWithoutErrorMessage())
                    showStepsList.insert(datasetType,1);
                else
                    showStepsList.insert(datasetType,0);
            }
            else if(datasetType == "TemplateDataset")
            {
                if(validationTemplateDatasetWithoutErrorMessage())
                    showStepsList.insert(datasetType,1);
                else
                    showStepsList.insert(datasetType,0);
            }
            else if(datasetType == "ParameterQuantificationDataset")
            {
                if(validationParameterQuantificationDatasetWithoutErrorMessage())
                    showStepsList.insert(datasetType,1);
                else
                    showStepsList.insert(datasetType,0);
            }
            else if(datasetType == "SpectDataset")
            {
                if(validationSpectDatasetWithoutErrorMessage())
                    showStepsList.insert(datasetType,1);
                else
                    showStepsList.insert(datasetType,0);
            }
            else if((datasetType == "MeshDataset") || (datasetType == "RegistrationDataset") || (datasetType == "StatisticalDataset")|| (datasetType == "CtDataset")|| (datasetType == "SegmentationDataset"))
            {
                if(validationStandardDataset())
                    showStepsList.insert(datasetType,1);
                else
                    showStepsList.insert(datasetType,0);
            }
        }

        emit callBuildUpdateSteps(showStepsList);
    }
}

void QtShanoirUploadWidgetDatasetTypeDetails::fillComboBox()
{
    ui->datasetTypeComboBox->clear();
    if (!datasetTypeSelectedList.isEmpty())
    {
        ui->datasetTypeComboBox->insertItem(0,"");
        for (int i=0; i<datasetTypeSelectedList.size();i++)
            ui->datasetTypeComboBox->insertItem(i+1,datasetTypeSelectedList.value(i));
    }
}
void QtShanoirUploadWidgetDatasetTypeDetails::attachShowStepsWidget(QtShanoirUploadWidgetShowStepsDatasetTypeDetails* widget)
{
    showsteps = widget;
}


void QtShanoirUploadWidgetDatasetTypeDetails::clearWidget()
{
    if (ui->gridLayout->count() == 4)
    {
        QWidget* widget = ui->gridLayout->itemAt(3)->widget();
        ui->gridLayout->removeWidget(widget);
        delete widget;
    }
}
void QtShanoirUploadWidgetDatasetTypeDetails::showWidget(QString datasetType)
{
    clearWidget();
    if(datasetType == "MrDataset")
    {
        QtShanoirUploadWidgetDatasetTypeDetailsMrDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasetTypeDetailsMrDataset(mrDatasetFilesToUpload);
        ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
        connect(processedDatasetDetailsTable, SIGNAL(callUpdateMrDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateMrDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));

    }
    else if(datasetType == "MrSpectroscopyDataset")
    {
        QtShanoirUploadWidgetDatasetTypeDetailsMrSpectroscopyDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasetTypeDetailsMrSpectroscopyDataset(mrSpectroscopyDatasetFilesToUpload);
        ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
        connect(processedDatasetDetailsTable, SIGNAL(callUpdateMrSpectroscopyDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateMrSpectroscopyDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));

    }
    else if(datasetType == "CalibrationDataset")
    {
        QtShanoirUploadWidgetDatasetTypeDetailsCalibrationDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasetTypeDetailsCalibrationDataset(calibrationFilesToUpload);
        ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
        connect(processedDatasetDetailsTable, SIGNAL(callUpdateCalibrationDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateCalibrationDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));

    }
    else if((datasetType == "EegDataset") || (datasetType == "MegDataset") || (datasetType == "PetDataset"))
    {
        if (datasetType == "EegDataset")
        {
            QtShanoirUploadWidgetDatasetTypeDetailsEegMegPetDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasetTypeDetailsEegMegPetDataset(eegFilesToUpload);
            ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
            connect(processedDatasetDetailsTable, SIGNAL(callUpdateEegMegPetDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateEegMegPetDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));
        }
        else if (datasetType == "MegDataset")
        {
            QtShanoirUploadWidgetDatasetTypeDetailsEegMegPetDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasetTypeDetailsEegMegPetDataset(megFilesToUpload);
            ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
            connect(processedDatasetDetailsTable, SIGNAL(callUpdateEegMegPetDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateEegMegPetDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));
        }
        else if (datasetType == "PetDataset")
        {
            QtShanoirUploadWidgetDatasetTypeDetailsEegMegPetDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasetTypeDetailsEegMegPetDataset(petFilesToUpload);
            ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
            connect(processedDatasetDetailsTable, SIGNAL(callUpdateEegMegPetDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateEegMegPetDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));
        }
    }
    else if(datasetType == "TemplateDataset")
    {
        QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset(templateFilesToUpload);
        ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
        connect(processedDatasetDetailsTable, SIGNAL(callUpdateTemplateDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateTemplateDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));
    }
    else if(datasetType == "ParameterQuantificationDataset")
    {
        QtShanoirUploadWidgetDatasetTypeDetailsParameterQuantificationDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasetTypeDetailsParameterQuantificationDataset(parameterQuantificationFilesToUpload);
        ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
        connect(processedDatasetDetailsTable, SIGNAL(callUpdateParameterQuantificationDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateParameterQuantificationDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));

    }
    else if(datasetType == "SpectDataset")
    {
        QtShanoirUploadWidgetDatasettypeDetailsSpectDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasettypeDetailsSpectDataset(spectFilesToUpload);
        ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
        connect(processedDatasetDetailsTable, SIGNAL(callUpdateSpectDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateSpectDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));
    }
    else if((datasetType == "MeshDataset") || (datasetType == "RegistrationDataset") || (datasetType == "StatisticalDataset")|| (datasetType == "CtDataset")|| (datasetType == "SegmentationDataset"))
    {
        if (datasetType == "MeshDataset")
        {
            QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset(meshFilesToUpload);
            ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
            connect(processedDatasetDetailsTable, SIGNAL(callUpdateStandardDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateStandardDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));
        }
        else if (datasetType == "RegistrationDataset")
        {
            QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset(registrationFilesToUpload);
            ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
            connect(processedDatasetDetailsTable, SIGNAL(callUpdateStandardDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateStandardDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));
        }
        else if (datasetType == "StatisticalDataset")
        {
            QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset(statisticalFilesToUpload);
            ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
            connect(processedDatasetDetailsTable, SIGNAL(callUpdateStandardDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateStandardDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));
        }
        else if (datasetType == "CtDataset")
        {
            QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset(ctFilesToUpload);
            ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
            connect(processedDatasetDetailsTable, SIGNAL(callUpdateStandardDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateStandardDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));
        }
        else if (datasetType == "SegmentationDataset")
        {
            QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset* processedDatasetDetailsTable = new QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset(segmentationFilesToUpload);
            ui->gridLayout->addWidget(processedDatasetDetailsTable,2,1);
            connect(processedDatasetDetailsTable, SIGNAL(callUpdateStandardDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)), this, SLOT(updateStandardDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));
        }
    }

    //type not supported ==> error

}

void QtShanoirUploadWidgetDatasetTypeDetails::updateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp> list)
{
    this->filesToUpload = list;
    clearIntermediateLists();
    fillUpdateIntermediateLists();
}

void QtShanoirUploadWidgetDatasetTypeDetails::fillUpdateIntermediateLists()
{
    for (int i=0;i<filesToUpload.size();i++)  // ou on peut raisonner sur la list des dataset type selected
    {
        if (filesToUpload[i].getDatasetClass() == "MrDataset")
        {
            mrDatasetFilesToUploadPositions.append(i);
            mrDatasetFilesToUpload.append(filesToUpload[i]);
        }
        else if (filesToUpload[i].getDatasetClass() == "MrSpectroscopyDataset")
        {
            mrSpectroscopyDatasetFilesToUploadPositions.append(i);
            mrSpectroscopyDatasetFilesToUpload.append(filesToUpload[i]);
        }
        else if (filesToUpload[i].getDatasetClass() == "CalibrationDataset")
        {
            calibrationFilesToUploadPositions.append(i);
            calibrationFilesToUpload.append(filesToUpload[i]);
        }
        else if (filesToUpload[i].getDatasetClass() == "EegDataset")
        {
            eegFilesToUploadPositions.append(i);
            eegFilesToUpload.append(filesToUpload[i]);
        }
        else if (filesToUpload[i].getDatasetClass() == "MegDataset")
        {
            megFilesToUploadPositions.append(i);
            megFilesToUpload.append(filesToUpload[i]);
        }
        else if (filesToUpload[i].getDatasetClass() == "PetDataset")
        {
            petFilesToUploadPositions.append(i);
            petFilesToUpload.append(filesToUpload[i]);
        }
        else if (filesToUpload[i].getDatasetClass() == "TemplateDataset")
        {
            templateFilesToUploadPositions.append(i);
            templateFilesToUpload.append(filesToUpload[i]);
        }
        else if (filesToUpload[i].getDatasetClass() == "ParameterQuantificationDataset")
        {
            parameterQuantificationFilesToUploadPositions.append(i);
            parameterQuantificationFilesToUpload.append(filesToUpload[i]);
        }
        else if (filesToUpload[i].getDatasetClass() == "SpectDataset")
        {
            spectFilesToUploadPositions.append(i);
            spectFilesToUpload.append(filesToUpload[i]);
        }
        else if (filesToUpload[i].getDatasetClass() == "MeshDataset")
        {
            meshFilesToUploadPositions.append(i);
            meshFilesToUpload.append(filesToUpload[i]);
        }
        else if (filesToUpload[i].getDatasetClass() == "RegistrationDataset")
        {
            registrationFilesToUploadPositions.append(i);
            registrationFilesToUpload.append(filesToUpload[i]);
        }
        else if (filesToUpload[i].getDatasetClass() == "StatisticalDataset")
        {
            statisticalFilesToUploadPositions.append(i);
            statisticalFilesToUpload.append(filesToUpload[i]);
        }
        else if (filesToUpload[i].getDatasetClass() == "CtDataset")
        {
            ctFilesToUploadPositions.append(i);
            ctFilesToUpload.append(filesToUpload[i]);
        }
        else if (filesToUpload[i].getDatasetClass() == "SegmentationDataset")
        {
            segmentationFilesToUploadPositions.append(i);
            segmentationFilesToUpload.append(filesToUpload[i]);
        }
    }
    updateShowStepsList();
}

void QtShanoirUploadWidgetDatasetTypeDetails::clearIntermediateLists()
{
    mrDatasetFilesToUpload.clear();
    mrSpectroscopyDatasetFilesToUpload.clear();
    calibrationFilesToUpload.clear();
    eegFilesToUpload.clear();
    megFilesToUpload.clear();
    petFilesToUpload.clear();
    templateFilesToUpload.clear();
    parameterQuantificationFilesToUpload.clear();
    spectFilesToUpload.clear();
    meshFilesToUpload.clear();
    registrationFilesToUpload.clear();
    statisticalFilesToUpload.clear();
    ctFilesToUpload.clear();
    segmentationFilesToUpload.clear();
    mrDatasetFilesToUploadPositions.clear();
    mrSpectroscopyDatasetFilesToUploadPositions.clear();
    calibrationFilesToUploadPositions.clear();
    eegFilesToUploadPositions.clear();
    megFilesToUploadPositions.clear();
    petFilesToUploadPositions.clear();
    templateFilesToUploadPositions.clear();
    parameterQuantificationFilesToUploadPositions.clear();
    spectFilesToUploadPositions.clear();
    meshFilesToUploadPositions.clear();
    registrationFilesToUploadPositions.clear();
    statisticalFilesToUploadPositions.clear();
    ctFilesToUploadPositions.clear();
    segmentationFilesToUploadPositions.clear();
}

void QtShanoirUploadWidgetDatasetTypeDetails::updateMrDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp> list)
{
    this->mrDatasetFilesToUpload = list;
    updateShowStepsList();
}

void QtShanoirUploadWidgetDatasetTypeDetails::updateMrSpectroscopyDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp> list)
{
    this->mrSpectroscopyDatasetFilesToUpload = list;
    updateShowStepsList();

}

void QtShanoirUploadWidgetDatasetTypeDetails::updateCalibrationDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp> list)
{
    this->calibrationFilesToUpload = list;
    updateShowStepsList();
}

void QtShanoirUploadWidgetDatasetTypeDetails::updateEegMegPetDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp> list)
{
    if (list[0].getDatasetClass() == "EegDataset")
        this->eegFilesToUpload = list;
    else if (list[0].getDatasetClass() == "MegDataset")
        this->megFilesToUpload = list;
    else if (list[0].getDatasetClass() == "PetDataset")
        this->petFilesToUpload = list;
    updateShowStepsList();

}

void QtShanoirUploadWidgetDatasetTypeDetails::updateParameterQuantificationDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp> list)
{
    this->parameterQuantificationFilesToUpload = list;
    updateShowStepsList();

}

void QtShanoirUploadWidgetDatasetTypeDetails::updateSpectDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp> list)
{
    this->spectFilesToUpload = list;
    updateShowStepsList();

}

void QtShanoirUploadWidgetDatasetTypeDetails::updateTemplateDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp> list)
{
    this->templateFilesToUpload = list;
    updateShowStepsList();

}

void QtShanoirUploadWidgetDatasetTypeDetails::updateStandardDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp> list)
{
    if (list[0].getDatasetClass() == "MeshDataset")
        this->meshFilesToUpload = list;
    else if (list[0].getDatasetClass() == "RegistrationDataset")
        this->registrationFilesToUpload = list;
    else if (list[0].getDatasetClass() == "StatisticalDataset")
        this->statisticalFilesToUpload = list;
    else if (list[0].getDatasetClass() == "CtDataset")
        this->ctFilesToUpload = list;
    else if (list[0].getDatasetClass() == "SegmentationDataset")
        this->segmentationFilesToUpload = list;
    updateShowStepsList();
}

void QtShanoirUploadWidgetDatasetTypeDetails::submitFilesToUpload()
{
    if(!mrDatasetFilesToUploadPositions.isEmpty())
        for(int i=0; i<mrDatasetFilesToUploadPositions.size();i++)
            filesToUpload.replace(mrDatasetFilesToUploadPositions[i],mrDatasetFilesToUpload[i]);
    if(!mrSpectroscopyDatasetFilesToUploadPositions.isEmpty())
        for(int i=0; i<mrSpectroscopyDatasetFilesToUploadPositions.size();i++)
            filesToUpload.replace(mrSpectroscopyDatasetFilesToUploadPositions[i],mrSpectroscopyDatasetFilesToUpload[i]);
    if(!calibrationFilesToUploadPositions.isEmpty())
        for(int i=0; i<calibrationFilesToUploadPositions.size();i++)
            filesToUpload.replace(calibrationFilesToUploadPositions[i],calibrationFilesToUpload[i]);
    if(!eegFilesToUploadPositions.isEmpty())
        for(int i=0; i<eegFilesToUploadPositions.size();i++)
            filesToUpload.replace(eegFilesToUploadPositions[i],eegFilesToUpload[i]);
    if(!megFilesToUploadPositions.isEmpty())
        for(int i=0; i<megFilesToUploadPositions.size();i++)
            filesToUpload.replace(megFilesToUploadPositions[i],megFilesToUpload[i]);
    if(!petFilesToUploadPositions.isEmpty())
        for(int i=0; i<petFilesToUploadPositions.size();i++)
            filesToUpload.replace(petFilesToUploadPositions[i],petFilesToUpload[i]);
    if(!templateFilesToUploadPositions.isEmpty())
        for(int i=0; i<templateFilesToUploadPositions.size();i++)
            filesToUpload.replace(templateFilesToUploadPositions[i],templateFilesToUpload[i]);
    if(!parameterQuantificationFilesToUploadPositions.isEmpty())
        for(int i=0; i<parameterQuantificationFilesToUploadPositions.size();i++)
            filesToUpload.replace(parameterQuantificationFilesToUploadPositions[i],parameterQuantificationFilesToUpload[i]);
    if(!spectFilesToUploadPositions.isEmpty())
        for(int i=0; i<spectFilesToUploadPositions.size();i++)
            filesToUpload.replace(spectFilesToUploadPositions[i],spectFilesToUpload[i]);
    if(!meshFilesToUploadPositions.isEmpty())
        for(int i=0; i<meshFilesToUploadPositions.size();i++)
            filesToUpload.replace(meshFilesToUploadPositions[i],meshFilesToUpload[i]);
    if(!registrationFilesToUploadPositions.isEmpty())
        for(int i=0; i<registrationFilesToUploadPositions.size();i++)
            filesToUpload.replace(registrationFilesToUploadPositions[i],registrationFilesToUpload[i]);
    if(!statisticalFilesToUploadPositions.isEmpty())
        for(int i=0; i<statisticalFilesToUploadPositions.size();i++)
            filesToUpload.replace(statisticalFilesToUploadPositions[i],statisticalFilesToUpload[i]);
    if(!ctFilesToUploadPositions.isEmpty())
        for(int i=0; i<ctFilesToUploadPositions.size();i++)
            filesToUpload.replace(ctFilesToUploadPositions[i],ctFilesToUpload[i]);
    if(!segmentationFilesToUploadPositions.isEmpty())
        for(int i=0; i<segmentationFilesToUploadPositions.size();i++)
            filesToUpload.replace(segmentationFilesToUploadPositions[i],segmentationFilesToUpload[i]);
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validatePage()
{
    bool validation = validationMrDataset() && validationMrSpectroscopyDataset() && validationCalibrationDataset() && validationEegMegPetDataset() && validationParameterQuantificationDataset() && validationSpectDataset() && validationTemplateDataset() && validationStandardDataset();
    if (validation)
    {
        submitFilesToUpload();

        QList<struct ProcessedDatasetFilesAndAttributes*> str_filesToUpload;
        for(int i=0; i<filesToUpload.size();i++)
        {
            struct ProcessedDatasetFilesAndAttributes* str_processedDataset = new struct ProcessedDatasetFilesAndAttributes;
            str_processedDataset->filename = filesToUpload[i].getFilename();
            str_processedDataset->studyId = filesToUpload[i].getStudyId();
            str_processedDataset->inputDatasetIdList = filesToUpload[i].getInputDatasetIdList();
            str_processedDataset->refDatasetProcessingId = filesToUpload[i].getRefDatasetProcessingId();
            str_processedDataset->datasetClass = filesToUpload[i].getDatasetClass();
            str_processedDataset->datasetName = filesToUpload[i].getDatasetName();
            str_processedDataset->datasetComment = filesToUpload[i].getDatasetComment();
            str_processedDataset->refMrDatasetNatureId = filesToUpload[i].getRefMrDatasetNatureId();
            str_processedDataset->refMrQualityProcedureTypeId = filesToUpload[i].getRefMrQualityProcedureTypeId();
            str_processedDataset->refCalibrationDatasetTypeId = filesToUpload[i].getRefCalibrationDatasetTypeId();
            str_processedDataset->refProcessedDatasetTypeId = filesToUpload[i].getRefProcessedDatasetTypeId();
            str_processedDataset->refParameterQuantificationDatasetNatureId = filesToUpload[i].getRefParameterQuantificationDatasetNatureId();
            str_processedDataset->refSpectDatasetNatureId = filesToUpload[i].getRefSpectDatasetNatureId();
            str_processedDataset->refTemplateDatasetNatureId = filesToUpload[i].getRefTemplateDatasetNatureId();

            str_filesToUpload.append(str_processedDataset);
        }


        QLibrary library("DAO.dll");
        if (!library.load())
                qDebug() << library.errorString();
        else
                qDebug() << "library loaded";
        typedef void (* CallFunction)(QList<struct ProcessedDatasetFilesAndAttributes*>);
        CallFunction cf = (CallFunction)library.resolve("uploadProcessedDatasetFiles");
        if (cf)
        {
              cf(str_filesToUpload);
        }
        else
            qDebug() << "could not call function";


    }
    return validation;
}

QString QtShanoirUploadWidgetDatasetTypeDetails::reduceFilenameToTwoDir(QString filename)
{
    QString inter1 = filename.left(filename.lastIndexOf("/"));
    QString inter2 = inter1.left(inter1.lastIndexOf("/"));
    if (inter2.lastIndexOf("/") != -1)
    {
        return filename.right(filename.size()-inter2.lastIndexOf("/"));
    }
     else
        return filename;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationMrDataset()
{
    if(!mrDatasetFilesToUpload.isEmpty())
        for(int i=0; i<mrDatasetFilesToUpload.size();i++)
        {
            QString filename = reduceFilenameToTwoDir(mrDatasetFilesToUpload[i].getFilename());
            if (mrDatasetFilesToUpload[i].getRefMrDatasetNatureId() == 0)
            {
                QString message = QString("MrDataset Nature for file << %1 >> in row %2 is null in MrDataset section.").arg(filename).arg(QString::number(i));
                QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
                return false;
            }
            else if (mrDatasetFilesToUpload[i].getRefMrQualityProcedureTypeId() == 0)
            {
                QString message = QString("MrDataset Quality Procedure Type for file << %1 >> in row %2 is null in MrDataset section.").arg(filename).arg(QString::number(i));
                QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
                return false;
            }
        }
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationMrDatasetWithoutErrorMessage()
{
    if(!mrDatasetFilesToUpload.isEmpty())
        for(int i=0; i<mrDatasetFilesToUpload.size();i++)
            if (mrDatasetFilesToUpload[i].getRefMrDatasetNatureId() == 0)
                return false;
            else if (mrDatasetFilesToUpload[i].getRefMrQualityProcedureTypeId() == 0)
                return false;
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationMrSpectroscopyDataset()
{
    if(!mrSpectroscopyDatasetFilesToUpload.isEmpty())
        for(int i=0; i<mrSpectroscopyDatasetFilesToUpload.size();i++)
        {
            QString filename = reduceFilenameToTwoDir(mrSpectroscopyDatasetFilesToUpload[i].getFilename());
            if (mrSpectroscopyDatasetFilesToUpload[i].getRefMrDatasetNatureId() == 0)
            {
                QString message = QString("MrSpectroscopyDataset Nature for file << %1 >> in row %2 is null in MrSpectroscopyDataset section.").arg(filename).arg(QString::number(i));
                QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
                return false;
            }
            else if (mrSpectroscopyDatasetFilesToUpload[i].getRefMrQualityProcedureTypeId() == 0)
            {
                QString message = QString("MrDataset Quality Procedure Type for file << %1 >> in row %2 is null in MrSpectroscopyDataset section.").arg(filename).arg(QString::number(i));
                QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
                return false;
            }
        }
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationMrSpectroscopyDatasetWithoutErrorMessage()
{
    if(!mrSpectroscopyDatasetFilesToUpload.isEmpty())
        for(int i=0; i<mrSpectroscopyDatasetFilesToUpload.size();i++)
            if (mrSpectroscopyDatasetFilesToUpload[i].getRefMrDatasetNatureId() == 0)
                return false;
            else if (mrSpectroscopyDatasetFilesToUpload[i].getRefMrQualityProcedureTypeId() == 0)
                return false;
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationCalibrationDataset()
{
    if(!calibrationFilesToUpload.isEmpty())
        for(int i=0; i<calibrationFilesToUpload.size();i++)
        {
            if (calibrationFilesToUpload[i].getRefCalibrationDatasetTypeId() == 0)
            {
                QString filename = reduceFilenameToTwoDir(calibrationFilesToUpload[i].getFilename());
                QString message = QString("Calibration Dataset Type for file << %1 >> in row %2 is null in CalibrationDataset section.").arg(filename).arg(QString::number(i));
                QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
                return false;
            }
        }
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationCalibrationDatasetWithoutErrorMessage()
{
    if(!calibrationFilesToUpload.isEmpty())
    for(int i=0; i<calibrationFilesToUpload.size();i++)
        if (calibrationFilesToUpload[i].getRefCalibrationDatasetTypeId() == 0)
            return false;
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationEegMegPetDataset()
{
    if (!eegFilesToUpload.isEmpty())
        for(int i=0; i<eegFilesToUpload.size();i++)
        {
            if (eegFilesToUpload[i].getRefProcessedDatasetTypeId() == 0)
            {
                QString filename = reduceFilenameToTwoDir(eegFilesToUpload[i].getFilename());
                QString message = QString("Processed Dataset Type for file << %1 >> in row %2 is null in EegDataset section.").arg(filename).arg(QString::number(i));
                QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
                return false;
            }
        }
    else if (!megFilesToUpload.isEmpty())
        for(int i=0; i<megFilesToUpload.size();i++)
        {
            if (megFilesToUpload[i].getRefProcessedDatasetTypeId() == 0)
            {
                QString filename = reduceFilenameToTwoDir(megFilesToUpload[i].getFilename());
                QString message = QString("Processed Dataset Type for file << %1 >> in row %2 is null in MegDataset section.").arg(filename).arg(QString::number(i));
                QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
                return false;
            }
        }
    else if (!petFilesToUpload.isEmpty())
        for(int i=0; i<petFilesToUpload.size();i++)
        {
            if (petFilesToUpload[i].getRefProcessedDatasetTypeId() == 0)
            {
                QString filename = reduceFilenameToTwoDir(petFilesToUpload[i].getFilename());
                QString message = QString("Processed Dataset Type for file << %1 >> in row %2 is null in PetDataset section.").arg(filename).arg(QString::number(i));
                QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
                return false;
            }
        }
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationEegMegPetDatasetWithoutErrorMessage()
{
    if (!eegFilesToUpload.isEmpty())
    {
        for(int i=0; i<eegFilesToUpload.size();i++)
            if (eegFilesToUpload[i].getRefProcessedDatasetTypeId() == 0)
                return false;
    }
    else if (!megFilesToUpload.isEmpty())
        for(int i=0; i<megFilesToUpload.size();i++)
        {
            if (megFilesToUpload[i].getRefProcessedDatasetTypeId() == 0)
                return false;
        }
    else if (!petFilesToUpload.isEmpty())
        for(int i=0; i<petFilesToUpload.size();i++)
        {
            if (petFilesToUpload[i].getRefProcessedDatasetTypeId() == 0)
                return false;
        }
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationParameterQuantificationDataset()
{
    if (!parameterQuantificationFilesToUpload.isEmpty())
        for(int i=0; i<parameterQuantificationFilesToUpload.size();i++)
        {
            if (parameterQuantificationFilesToUpload[i].getRefParameterQuantificationDatasetNatureId() == 0)
            {
                QString filename = reduceFilenameToTwoDir(parameterQuantificationFilesToUpload[i].getFilename());
                QString message = QString("Parameter Quantification Dataset Nature for file << %1 >> in row %2 is null in ParameterQuantificationDataset section.").arg(filename).arg(QString::number(i));
                QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
                return false;
            }
        }
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationParameterQuantificationDatasetWithoutErrorMessage()
{
    if(!parameterQuantificationFilesToUpload.isEmpty())
    for(int i=0; i<parameterQuantificationFilesToUpload.size();i++)
        if (parameterQuantificationFilesToUpload[i].getRefParameterQuantificationDatasetNatureId() == 0)
            return false;
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationSpectDataset()
{
    for(int i=0; i<spectFilesToUpload.size();i++)
    {
        QString filename = reduceFilenameToTwoDir(spectFilesToUpload[i].getFilename());
        if (spectFilesToUpload[i].getRefSpectDatasetNatureId() == 0)
        {
            QString message = QString("Spect Dataset Nature for file << %1 >> in row %2 is null in SpectDataset section.").arg(filename).arg(QString::number(i));
            QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
            return false;
        }
        else if (spectFilesToUpload[i].getRefProcessedDatasetTypeId() == 0)
        {
            QString message = QString("Processed Dataset Type for file << %1 >> in row %2 is null in SpectDataset section.").arg(filename).arg(QString::number(i));
            QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
            return false;
        }
    }
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationSpectDatasetWithoutErrorMessage()
{
    if(!spectFilesToUpload.isEmpty())
        for(int i=0; i<spectFilesToUpload.size();i++)
        {
            if (spectFilesToUpload[i].getRefSpectDatasetNatureId() == 0)
                return false;
            else if (spectFilesToUpload[i].getRefProcessedDatasetTypeId() == 0)
                return false;
        }
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationTemplateDataset()
{
    if (!templateFilesToUpload.isEmpty())
        for(int i=0; i<templateFilesToUpload.size();i++)
        {
            if (templateFilesToUpload[i].getRefTemplateDatasetNatureId() == 0)
            {
                QString filename = reduceFilenameToTwoDir(templateFilesToUpload[i].getFilename());
                QString message = QString("Template Dataset Type for file << %1 >> in row %2 is null in TemplateDataset section.").arg(filename).arg(QString::number(i));
                QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
                return false;
            }
        }
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationTemplateDatasetWithoutErrorMessage()
{
    if (!templateFilesToUpload.isEmpty())
        for(int i=0; i<templateFilesToUpload.size();i++)
            if (templateFilesToUpload[i].getRefTemplateDatasetNatureId() == 0)
                return false;
    return true;
}

bool QtShanoirUploadWidgetDatasetTypeDetails::validationStandardDataset()
{
    return true;
}
