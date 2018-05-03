Stitcher::Status Stitcher::stitch(InputArray images, OutputArray pano)
{
    Status status = estimateTransform(images);
    if (status != OK)
        return status;
    return composePanorama(pano);
}


Stitcher::Status Stitcher::estimateTransform(InputArray images, const vector<vector<Rect> > &rois)
{
    images.getMatVector(imgs_);
    rois_ = rois;

    Status status;

    if ((status = matchImages()) != OK)
        return status;

    estimateCameraParams();

    return OK;
}


Stitcher::Status Stitcher::composePanorama(OutputArray pano)
{
    return composePanorama(vector<Mat>(), pano);
}
