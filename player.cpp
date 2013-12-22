/**
    This class acquires frames from the camera, detects the faces,
    and emit the images to the GUI
*/

#include "player.h"

// The constructor
Player::Player(QObject *parent)
 : QThread(parent)
{
    // Video is stopped
    stop = false;
}

/**
 * This function checks the avaibility of the camera
 * @return true If the camera is opened
 *         false If the camera cannot be found
 */
bool Player::openCamera()
{
    capture.open(0);

    if (capture.isOpened())
        return true;
    return false;
}

/**
 * This function plays the video acquired from the
 * camera
 */
void Player::Play()
{
    if (isStopped())
        stop = false;
    start(NormalPriority);

}

/**
 * This function run the video, get the frames, detects the faces,
 * converts them to QImage, and image them to the GUI
 */
void Player::run()
{
    // Get the haarcascade file's name
    String cascade_name = "/home/brian/Documents/C and C++ Program/GuiWebcam/hat_cascade.xml";
    // Create the cascade classifer
    CascadeClassifier cascade;
    // Load cascade classifer
    cascade.load(cascade_name);

    int delay = (1000/frameRate);

    while (!stop) {
        // Get the frame from the camera
        capture >> frame;

        // Get the non-empty frame
        if (!frame.empty()) {
            // Resize the frame to 400x200
            resize(frame, frame, Size(400, 200), 0, 0, INTER_LINEAR);

            //Detect Faces:
            std::vector<Rect> hats;
            Mat frame_gray;

            cvtColor( frame, frame_gray, CV_BGR2GRAY );

            // Detect faces
            cascade.detectMultiScale(frame_gray, hats);

            for(unsigned long i = 0; i < hats.size(); i++ )
                // Draw rectangles on the detected faces
                rectangle(frame, hats[i],CV_RGB(0, 255, 0), 2);


            cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
            // Convert frame to QImage
            img = QImage((const unsigned char*)(RGBframe.data),
                          RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
            // Emit the images to the GUI
            emit processedImage(img);
            this->msleep(delay);
        }
    }

}

// The destructor
Player::~Player()
{
    mutex.lock();
    stop = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

/**
 * This function stops the video stream
 */
void Player::Stop()
{
    stop = true;
}

/**
 * This function checks whether the video is stopped
 */
bool Player::isStopped() const{
    return this->stop;
}

void Player::msleep(int ms){
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}
