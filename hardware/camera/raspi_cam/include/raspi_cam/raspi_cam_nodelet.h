#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <raspicam/raspicam_cv.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace raspi_cam
{
    class RaspiCamNodelet : public nodelet::Nodelet
    {
        public:
            virtual void onInit();

            void Setup(ros::NodeHandle nh);
        private:
            void runPublisher();
            void convertImage(cv::Mat& image, cv_bridge::CvImagePtr& cv_ptr);
            image_transport::ImageTransport it_;
            raspicam::RaspiCam_Cv camera_;
            ros::NodeHandle nh_;
            image_transport::Publisher image_pub_;

    };
}//end raspi_cam namespace