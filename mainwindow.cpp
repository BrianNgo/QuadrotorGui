#include "mainwindow.h"
#include "ui_mainwindow.h"

// The constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Create the Player object
    myPlayer = new Player();

    // Processing the images by connecting the signal and the slot
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),
                              this, SLOT(updatePlayerUI(QImage)));
    // Set up the UI's label
    ui->setupUi(this);

    // Set up the webView of the UI
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled,true);
    ui->webView->settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled,true);
    ui->webView->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,true);
    ui->webView->settings()->setAttribute(QWebSettings::LocalStorageEnabled,true);
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard,true);
    ui->webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled,true);
    ui->webView->settings()->setAttribute(QWebSettings::CanvasPathEnabled, true);
    ui->webView->load(QUrl("file:///home/brian/Documents/C%20and%20C++%20Program/GuiWebcam/map.html"));
}

/**
 * This function receives the frames from the Player object and update
 * the UI's label
 * @param img
 */
void MainWindow::updatePlayerUI(QImage img)
{
    // The image is not null
    if (!img.isNull())
    {
        // Get the dimension available on this screen
        ui->label_1->setAlignment(Qt::AlignCenter);
        // Display the image
        ui->label_1->setPixmap(QPixmap::fromImage(img).scaled(ui->label_1->size(),
                                                            Qt::KeepAspectRatio,
                                                            Qt::FastTransformation));
    }
}

// The destructor
MainWindow::~MainWindow()
{
    delete myPlayer;
    delete ui;
}

/**
 * This function is the slot for loading the video
 */
void MainWindow::on_pushButton_clicked()
{
    // Check whether the camera is openned
    if (!myPlayer->openCamera())
    {
        QMessageBox msgBox;
        msgBox.setText("Camera is broken");
        msgBox.exec();
    }
    // Play the video
    myPlayer->Play();
}

/**
 * This function is the the slot for playing and stoping
 * the video
 */
void MainWindow::on_pushButton_2_clicked()
{
    // Check whether the video is stopped
    if (myPlayer->isStopped())
    {
        // Play the video
        myPlayer->Play();
        // Change the text on the button
        ui->pushButton_2->setText(tr("Stop"));
    }else {
        // Stop the video
        myPlayer->Stop();
        // Change the text on the button
        ui->pushButton_2->setText(tr("Play"));
    }
}


