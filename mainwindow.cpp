#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    QTimer *new_file_selection_timer = new QTimer(this);
    connect(new_file_selection_timer,SIGNAL(timeout()),this,SLOT(new_file_slection()));
    new_file_selection_timer->start(500);

    FileDetection *t = new FileDetection(ui->fileListWidget);
    t->start();

//    QTimer *folder_detect_timer = new QTimer(t);
//    connect(folder_detect_timer,SIGNAL(timeout()),this,SLOT(folder_detection()));
//    folder_detect_timer->start(500);

//    QTimer *test_loof_timer = new QTimer(t);
//    connect(test_loof_timer,SIGNAL(timeout()),this,SLOT(test_loof()));
//    test_loof_timer->start(500);

    qDebug()<<ui->fileListWidget->count();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::print_image(QString file_path)
{
    QPixmap pixmap;
    if(pixmap.load(file_path)){
        double pixmap_ratio = pixmap.width() / pixmap.height();
        double label_ratio = ui->image_label->width() / ui->image_label->height();

        if(pixmap_ratio > label_ratio) ui->image_label->setPixmap(pixmap.scaledToWidth(ui->image_label->width()));
        else ui->image_label->setPixmap(pixmap.scaledToHeight(ui->image_label->height()));
    }
}

void MainWindow::test_loof()
{
    int i=0;
    while(1)
    {
        qDebug()<<i++;
    }
}
//폴더 검사
void MainWindow::folder_detection()
{
    QDir directory("images/");
    QStringList filters;
    filters << "*.png" <<"*.jpg"<<"*.jpeg";

    directory.setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    QFileInfoList file_infolist = directory.entryInfoList(filters);

    int list_count = ui->fileListWidget->count();
    int file_existence_check[list_count]; // 파일 존재 여부 체크용 : 0 = 존재 하지 않음 1 = 존재 함
    //초기화
    for(int i = 0; i<list_count;i++) file_existence_check[i] = 0;

    foreach(QFileInfo info, file_infolist){ //
        bool duplicate_check = true;
        for(int i = 0;i<ui->fileListWidget->count();i++){ //
            if(info.fileName() == ui->fileListWidget->item(i)->text()){  // 중복 여부 체크
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
            ui->fileListWidget->addItem(item);
            if(m_change_check_==false) m_change_check_=true;
        }
    }
    for(int i = list_count-1 ; i >=0 ;i--) if(file_existence_check[i] == 0)
    {
        delete ui->fileListWidget->takeItem(i);  // 존재하지 않은 파일 삭제
        if(m_change_check_==false) m_change_check_ = true;
    }
    if(m_change_check_) new_file_slection();
}

void MainWindow::new_file_slection()
{
    if(m_change_check_){
        ui->fileListWidget->setCurrentRow(ui->fileListWidget->count()-1);
        print_image(ui->fileListWidget->item(ui->fileListWidget->currentRow())->data(1).toString());
        m_change_check_ = false;
    }
}
void MainWindow::on_prev_image_btn_clicked()
{
    if(ui->fileListWidget->currentRow()>0){
        ui->fileListWidget->setCurrentRow(ui->fileListWidget->currentRow()-1);
        print_image(ui->fileListWidget->item(ui->fileListWidget->currentRow())->data(1).toString());
    }
}

void MainWindow::on_next_image_btn_clicked()
{
    if(ui->fileListWidget->currentRow()<ui->fileListWidget->count()-1){
        ui->fileListWidget->setCurrentRow(ui->fileListWidget->currentRow()+1);
        print_image(ui->fileListWidget->item(ui->fileListWidget->currentRow())->data(1).toString());
    }
}

void MainWindow::on_quit_btn_clicked()
{
    this->close();
}

void MainWindow::on_fileListWidget_itemActivated(QListWidgetItem *item)
{
    print_image(item->data(1).toString());
}
