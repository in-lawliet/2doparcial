#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "muParser.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->plot_btn,SIGNAL(clicked()),this,SLOT(plot()));
    connect(ui->compute_btn,SIGNAL(clicked()),this,SLOT(compute()));
    connect(ui->determinate_btn,SIGNAL(clicked()),this,SLOT(determinate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readfile(){
    QString dir = QFileDialog::getOpenFileName(this,"Load file",".../","Data (*.dat)",nullptr);
    if(dir.isEmpty()){
        return;
    };
    FILE *f=nullptr;
    f=fopen(dir.toUtf8(),"rb");
    if(f==nullptr){
        qDebug()<<"error reading the file";
        return;
    }

    fseek(f,0,SEEK_END);
    data.size=ftell(f);
    data.size/=(4*sizeof(float));
    data.x.resize(data.size);
    data.y.resize(data.size);
    data.t.resize(data.size);
    data.b.resize(data.size);

    fseek(f,0,SEEK_SET);
    for(int i=0;i<data.size;i++){
        float aux=0;
        fread(&aux, sizeof(float),1,f);
        data.x[i]=(double)aux;
        fread(&aux, sizeof(float),1,f);
        data.y[i]=(double)aux;
        fread(&aux, sizeof(float),1,f);
        data.t[i]=(double)aux;
        fread(&aux, sizeof(float),1,f);
        data.b[i]=(double)aux;
    }
    fclose(f);
}

void MainWindow::plot(){
    //seteo de colores para la grafica:
    readfile();
    QPen pen;
    QBrush brush;
    QColor color;
    //Grafica x:
    if(ui->plot_x->graphCount()==0){
        ui->plot_x->addGraph();
    }
    pen.setColor(Qt::red);
    pen.setWidth(1);
    color.setRgb(248,124,99,80);
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    ui->plot_x->graph(0)->setBrush(brush);
    ui->plot_x->graph(0)->setPen(pen);
    ui->plot_x->graph(0)->setData(data.t,data.x);
    ui->plot_x->graph(0)->rescaleAxes();
    ui->plot_x->replot();

    //Grafica y:
    if(ui->plot_y->graphCount()==0){
        ui->plot_y->addGraph();
    }
    pen.setColor(Qt::blue);
    pen.setWidth(1);
    color.setRgb(0,100,255,80);
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    ui->plot_y->graph(0)->setBrush(brush);
    ui->plot_y->graph(0)->setPen(pen);
    ui->plot_y->graph(0)->setData(data.t,data.y);
    ui->plot_y->graph(0)->rescaleAxes();
    ui->plot_y->replot();

    //Grafica b:
    if(ui->plot_b->graphCount()==0){
        ui->plot_b->addGraph();
    }
    pen.setColor(Qt::yellow);
    pen.setWidth(1);
    color.setRgb(255,255,0,80);
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    ui->plot_b->graph(0)->setBrush(brush);
    ui->plot_b->graph(0)->setPen(pen);
    ui->plot_b->graph(0)->setData(data.t,data.b);
    ui->plot_b->graph(0)->rescaleAxes();
    ui->plot_b->replot();
}

void MainWindow::compute(){
    double area=0;
    double tmin=ui->tmin->text().toDouble();
    double tmax=ui->tmax->text().toDouble();
    int i=0;
    if(tmin<data.t[0] || tmax>data.t[data.size-1]){
        qDebug("out of range");
    }else{
        while(data.t[i]<tmax){
            if(data.t[i]>tmin){
                double dt=std::abs(data.t[i+1]-data.t[i]);
                area+=std::abs(data.b[i]+data.b[i+1])*dt/2.0;
            }
            i++;
        }
    }
    ui->energy->setText(QString::number(area));
}
void MainWindow::determinate(){
    double time=ui->time_value->text().toDouble();

    int ti=0;
    int td=data.size-1;
    int tmid=(td+ti)/2;
    if(time<data.t[0] || time>data.t[data.size-1]){
        qDebug()<<"out of range";
    }else{
        while((td-ti)>1){
            tmid=(td+ti)/2;
            if(data.t[tmid]>time){
                td=tmid;
            }else if(data.t[tmid]<time){
                ti=tmid;
            }else if(data.t[tmid]==time){
                break;
            }
            qDebug()<<data.t[tmid];
        }
    }
    ui->x_value->setText(QString::number(data.x[tmid]));
    ui->y_value->setText(QString::number(data.y[tmid]));
    ui->b_value->setText(QString::number(data.b[tmid]));
}
