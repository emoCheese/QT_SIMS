#include "adminpage.h"
#include "ui_adminpage.h"

#include <QMessageBox>
#include <QSqlError>

AdminPage::AdminPage(QWidget *parent, QSqlDatabase& DB)
    : QDialog(parent)
    , ui(new Ui::AdminPage)
    , m_DB(DB)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);   // 点击某一单元格时，整行将被选中。
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);   // 一次只能选择一行。
    ui->tableView->setAlternatingRowColors(true);                          // 表格控件的交替行颜色

    initTableView();

}

AdminPage::~AdminPage()
{
    delete ui;
}

void AdminPage::showRecordCount()
{
    qDebug() << QString("记录条数：%1").arg(m_stuInfoTabModel->rowCount());
}

void AdminPage::initTableView()
{
    // 1 创建数据模型，打开数据表
    m_stuInfoTabModel = new QSqlRelationalTableModel(this, m_DB);
    m_stuInfoTabModel->setTable("studInfo");                                          // 设置（打开）数据表
    m_stuInfoTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);               // 数据保存方式 修改暂存，不提交
    m_stuInfoTabModel->setSort(m_stuInfoTabModel->fieldIndex("studID"), Qt::AscendingOrder);    // 排序
    // 创建选择模型
    m_selModel = new QItemSelectionModel(m_stuInfoTabModel, this);
    // 设置关联槽函数 当前项的变化
    connect(m_selModel, &QItemSelectionModel::currentRowChanged, this, &AdminPage::do_currentRowChanged);   // 当前行的变化

    if(!(m_stuInfoTabModel->select()))
    {
        QMessageBox::critical(this, "错误信息", "打开数据表错误，错误信息:\n"
                              + m_stuInfoTabModel->lastError().text());
        return;
    }
    showRecordCount();

    // 模型视图结构 设置 数据表模型 和 选择模型
    ui->tableView->setModel(m_stuInfoTabModel);
    ui->tableView->setSelectionModel(m_selModel);

    // 设置字段显示标题
    m_stuInfoTabModel->setHeaderData(m_stuInfoTabModel->fieldIndex("studID"), Qt::Horizontal, "学号");  // 设置表头
    m_stuInfoTabModel->setHeaderData(m_stuInfoTabModel->fieldIndex("name"), Qt::Horizontal, "姓名");
    m_stuInfoTabModel->setHeaderData(m_stuInfoTabModel->fieldIndex("gender"), Qt::Horizontal, "性别");
    m_stuInfoTabModel->setHeaderData(m_stuInfoTabModel->fieldIndex("age"), Qt::Horizontal, "年龄");
    m_stuInfoTabModel->setHeaderData(m_stuInfoTabModel->fieldIndex("departID"), Qt::Horizontal, "学院");
    m_stuInfoTabModel->setHeaderData(m_stuInfoTabModel->fieldIndex("majorID"), Qt::Horizontal, "专业");
    m_stuInfoTabModel->setHeaderData(m_stuInfoTabModel->fieldIndex("score"), Qt::Horizontal, "成绩");
    // 不在 tableView 中显示，对其进行隐藏
    m_stuInfoTabModel->setHeaderData(m_stuInfoTabModel->fieldIndex("photo"), Qt::Horizontal, "照片");
    ui->tableView->setColumnHidden(m_stuInfoTabModel->fieldIndex("photo"), true);


    m_stuInfoTabModel->setRelation(m_stuInfoTabModel->fieldIndex("departID"),
                                   QSqlRelation("departments", "departID", "department"));  // 学院
    m_stuInfoTabModel->setRelation(m_stuInfoTabModel->fieldIndex("majorID"),
                                   QSqlRelation("majors", "majorID", "major"));    // 专业

    // 为外键字段设置默认代理组件
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    // 查询数据表的数据  QSqlRelationalTableModel 需要 查询后才生效
    m_stuInfoTabModel->select();
    // 5 设置自定义代理
    QStringList strList;
    strList << "男" << "女";
    bool isEditable = false;
    delegateSex.setItems(strList, isEditable);
    ui->tableView->setItemDelegateForColumn(m_stuInfoTabModel->fieldIndex("gender"), &delegateSex);
    ui->tableView->setItemDelegateForColumn(m_stuInfoTabModel->fieldIndex("score"), &scoreDelegate);
    ui->tableView->setItemDelegateForColumn(m_stuInfoTabModel->fieldIndex("age"), &ageDelegate);

    // 手动触发点击事件，获取第一行的数据并展示
    ui->tableView->clicked(m_stuInfoTabModel->index(0, 0));

    getItem();

    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setModel(m_stuInfoTabModel);

    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    dataMapper->addMapping(ui->nameEdit_2, m_stuInfoTabModel->fieldIndex("name"));
    dataMapper->addMapping(ui->numEdit, m_stuInfoTabModel->fieldIndex("studID"));
    dataMapper->addMapping(ui->genderBox, m_stuInfoTabModel->fieldIndex("gender"));
    dataMapper->addMapping(ui->departBox, m_stuInfoTabModel->fieldIndex("department"));
    dataMapper->addMapping(ui->majorBox, m_stuInfoTabModel->fieldIndex("major"));
    dataMapper->addMapping(ui->scoreBox, m_stuInfoTabModel->fieldIndex("score"));
    dataMapper->addMapping(ui->ageBox, m_stuInfoTabModel->fieldIndex("age"));
    dataMapper->toFirst();


    // 获取第一行的索引
    QModelIndex firstIndex = m_stuInfoTabModel->index(0, 0);
    ui->tableView->clicked(firstIndex);
    updatePic(firstIndex);
}

void AdminPage::getItem()
{
    QStringList list;
    list << "生物科学学院" << "数理学院" << "化工学院" << "地球科学学院" << "信息科学学院" << "工程技术学院" << "商学院";
    ui->departBox->addItems(list);
    list.clear();
    list << "生物遗传工程" << "生物工程" << "量子物理学" << "天体物理学" << "固体地球物理学" << "计算机网络"
         << "软件工程" << "自动化" << "管理学" << "会计学";
    ui->majorBox->addItems(list);
}

void AdminPage::updatePic(const QModelIndex &current)
{
    if(!current.isValid())
    {
        qDebug() << "当前行数据无效";
        return;
    }
    int curRecNo = current.row();


    dataMapper->setCurrentIndex(curRecNo);
    QSqlRecord rec = m_stuInfoTabModel->record(curRecNo);
    if(rec.isNull("photo"))
    {
        ui->image_label->clear();
        qDebug() << "没有图像";
    }
    else
    {

        QByteArray data = rec.value("photo").toByteArray();
        QPixmap pic;
        pic.loadFromData(data);
        ui->image_label->setPixmap(pic.scaledToWidth(ui->image_label->size().width() / 2));
    }
    qDebug() << "更新展示数据";
}

void AdminPage::do_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{

}




void AdminPage::do_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    updatePic(current);
}

// 查询
void AdminPage::on_qureyBtn_clicked()
{
    QString name = ui->nameEdit->text();
    QString studID = ui->stuNoEdit->text();
    // 捏嘛嘛的，字符串搞错改半天
    // 通过设置 模型过滤器来筛选数据进行查询
    if(name != "" && studID != "")
        m_stuInfoTabModel->setFilter(QString("name='%1' AND studID=%2").arg(name).arg(studID));
    else if(name == "" && studID != "")
        m_stuInfoTabModel->setFilter(QString("studID=%1").arg(studID));
    else if(name != "" && studID == "")
        m_stuInfoTabModel->setFilter(QString("name='%1'").arg(name));
    updatePic(m_stuInfoTabModel->index(0,0));
}




// 全部显示
void AdminPage::on_showAllBtn_clicked()
{
    m_stuInfoTabModel->setFilter(QString(""));
}


void AdminPage::on_tableView_clicked(const QModelIndex &index)
{
    // 获取点击的行号
    int row = index.row();
    // 获取点击行的数据
    record = m_stuInfoTabModel->record(row);
    // 在控制台打印点击行的数据
    // qDebug() << "Clicked Row Data:";
    // for (int i = 0; i < record.count(); ++i)
    //     qDebug() << "fieldName" << i << ":" << record.fieldName(i);
    // for (int i = 0; i < record.count() - 1; ++i)
    //     qDebug() << "Column" << i << ":" << record.value(i).toString();
}


void AdminPage::on_saveBtn_clicked()
{
    bool res=m_stuInfoTabModel->submitAll();
    if (!res)
        QMessageBox::information(this, "消息", "数据保存错误,错误信息\n"+m_stuInfoTabModel->lastError().text());
}

// 添加数据
void AdminPage::on_insertBtn_clicked()
{
    //// 使用QSqlRecord
    QSqlRecord rec=m_stuInfoTabModel->record();      //获取一个空记录，只有字段定义
    rec.setValue(m_stuInfoTabModel->fieldIndex("empNo"),0);
    rec.setValue(m_stuInfoTabModel->fieldIndex("Gender"),"男");  //设置数据
    m_stuInfoTabModel->insertRecord(m_stuInfoTabModel->rowCount(),rec);   //插入到数据模型的最后

    m_selModel->clearSelection();
    QModelIndex curIndex=m_stuInfoTabModel->index(m_stuInfoTabModel->rowCount()-1,1);     //创建最后一行的ModelIndex
    m_selModel->setCurrentIndex(curIndex,QItemSelectionModel::Select);
}

// 删除数据
void AdminPage::on_deleteBtn_clicked()
{
    QModelIndex curIndex = m_selModel->currentIndex();
    m_stuInfoTabModel->removeRow(curIndex.row());
}

// 取消修改
void AdminPage::on_cancelBtn_clicked()
{
    m_stuInfoTabModel->revertAll();
}


// 修改图片
void AdminPage::on_picBtn_clicked()
{
    QString aFile=QFileDialog::getOpenFileName(this,"选择图片文件","","照片(*.jpg *.png)");
    if (aFile.isEmpty())
        return;

    // 读取图片
    QByteArray data;
    QFile* file=new QFile(aFile);
    file->open(QIODevice::ReadOnly);    //打开文件
    data = file->readAll();     //读取图片数据
    file->close();
    delete file;

    // 保存数据
    int curRecNo=m_selModel->currentIndex().row();    //当前记录的行号
    QSqlRecord  curRec=m_stuInfoTabModel->record(curRecNo);      //获取当前记录
    curRec.setValue("photo",data);  //设置字段数据
    m_stuInfoTabModel->setRecord(curRecNo,curRec);   //修改记录
    // 显示数据
    QPixmap pic;
    pic.load(aFile);  //在界面上显示
    ui->image_label->setPixmap(pic.scaledToWidth(ui->image_label->width()));
}

