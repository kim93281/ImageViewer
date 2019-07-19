#include "filedetection.h"


FileDetection::FileDetection(QListWidget *fileListWidget)
{
    this->fileListWidget = fileListWidget;
}

void FileDetection::run()
{
    while(1){
        if(fileListWidget!=nullptr)
        {
            qDebug()<<fileListWidget->count();
            QDir directory("images/");
            QStringList filters;
            filters << "*.png" <<"*.jpg"<<"*.jpeg";

            directory.setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
            QFileInfoList file_infolist = directory.entryInfoList(filters);

            int list_count = fileListWidget->count();
            int file_existence_check[list_count]; // 파일 존재 여부 체크용 : 0 = 존재 하지 않음 1 = 존재 함
            //초기화
            for(int i = 0; i<list_count;i++) file_existence_check[i] = 0;

            foreach(QFileInfo info, file_infolist){ //
                bool duplicate_check = true;
                for(int i = 0;i<fileListWidget->count();i++){ //
                    if(info.fileName() == fileListWidget->item(i)->text()){  // 중복 여부 체크
                        file_existence_check[i] = 1; //존재 여부 체크
                        if(duplicate_check == true) {duplicate_check = false;
                        }
                    }
                }

                if(duplicate_check){ //
                    QListWidgetItem *item = new QListWidgetItem();
                    item->setIcon(QIcon(info.fileName()));
                    item->setData(1,info.filePath());
                    item->setText(info.fileName());
                    fileListWidget->addItem(item);
                }
            }
            for(int i = list_count-1 ; i >=0 ;i--) if(file_existence_check[i] == 0)
            {
                delete fileListWidget->takeItem(i);  // 존재하지 않은 파일 삭제
            }

        }
        QThread::sleep(1);
    }
}
