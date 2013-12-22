#ifndef PLAYER_H
#define PLAYER_H
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class Player : public QThread
{    Q_OBJECT
 private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    VideoCapture capture;
    Mat RGBframe;
    Mat frame;
    int frameRate;
    QImage img;
 signals:
    //Signal to output frame to be displayed
    void processedImage(const QImage &image);
 protected:
     void run();
     void msleep(int ms);
 public:
    //Constructor
    Player(QObject *parent = 0);
    //Destructor
    ~Player();
    // Open the camera
    bool openCamera();
    //Play the stream
    void Play();
    //Stop the stream
    void Stop();
    //check if the player has been stopped
    bool isStopped() const;
};
#endif // VIDEOPLAYER_H
