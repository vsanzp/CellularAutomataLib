/*******************************************************************************************
 Author: 
        Victorino Sanz 
        Dpto. Informática y Automática, UNED
        Juan del Rosal, 16
        28040, Madrid
        Spain
        Email: vsanz@dia.uned.es
        http://www.euclides.dia.uned.es/vsanz

 Licensed by Victorino Sanz under the LGPL-3.0 or later
 Copyright © 2025, Victorino Sanz.

This program is free software: you can redistribute it and/or modify it under the terms of 
the GNU Leaser General Public License as published by the Free Software Foundation, either 
version 3 of the License, or  any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Leaser General Public License for more details.

You should have received a copy of the  GNU Leaser General Public License along with this 
program. If not, see <https://www.gnu.org/licenses/>.
*********************************************************************************************/
#ifndef CELLULARAUTOMATALIBANIM
#define CELLULARAUTOMATALIBANIM

#define OFFSET 10
#define STREAM_FRAME_RATE 30
#define STREAM_PIX_FMT  AV_PIX_FMT_YUV420P /* default pix_fmt */
#define SCALE_FLAGS SWS_BICUBIC

#include <CellularAutomataLib.c>

#include <raylib.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavutil/timestamp.h>



// a wrapper around a single output AVStream
typedef struct OutputStream {
    AVStream *st;
    AVCodecContext *enc;
    
    /* pts of the next frame that will be generated */
    int64_t next_pts;
    int samples_count;
    
    AVFrame *frame;
    //    AVFrame *tmp_frame;
    
    AVPacket *tmp_pkt;
    
    float t;
    //tincr, tincr2;
    
    struct SwsContext *sws_ctx;
    //    struct SwrContext *swr_ctx;
} OutputStream;

typedef struct Animation{
///    Cell ****M; // matrix of cells in the space 
///    Cell **A; // array of active cells
///    int n_A; // number of active cells
///    int X; // X size 
///    int Y; // Y size 
///    int Z; // Z size
///    int hex; // hexagonal 2D space
///    int ndims; // number of dimensions of the space
///    int **neighborhood; // topology of the neighborhood  (even neighborhood for hex spaces)
///    int **oddneighborhood; // for hex space
///    int n_neighbors; // number of neighbors
///    int n_inputs; // number of inputs
///    int plot_animation; // boolean flag to display graphical animation or not
///    int wrapped_borders; // space boundary configuration (like bitwise mask but using int: hundred for X, tens for Y and unit for Z)
///    int wrapx, wrapy,wrapz;
    void * space; // reference to the cellular space
    int storehistory; // flag to store and plot history in 1D
    double **hist; // 1D history of states
    int n_hist; // number of steps recorded in the history
    int save_video; // boolean flag to save animation in video using ffmpeg and libx264
    int wX,wY,wZ; // number of cells in each dimension of the animation window
    double sq; // square size for the raylib animation
    double displayDelay; // delay to display animation in gnuplot
    int plot_vector; // boolean flag to generate a vector space instead of scalar
    double (*display)(void*,int,int,int,double*,double*,double*,double*);
    // COLOR display(space, x, y, z, vectormodule, coord_x, coord_y, coord_z),
    // returns COLOR and double* params as VECTOR_MODULE, VECTOR_COORD_X, VECTOR_COORD_Y, VECTOR_COORD_Z for cell[x][y][z]
    Camera2D camera2; // camera for 2D animations
    Camera3D camera3; // camera for 3D animations
    //FILE * gp; // gnuplot terminal file descriptor
    
    int pts;
    OutputStream video_st;
    const AVCodec *video_codec;
    AVFormatContext *oc;
    const AVOutputFormat *fmt;
}Animation;


/* Add an output stream. */
static void add_stream(OutputStream *ost, AVFormatContext *oc,
                       const AVCodec **codec,
                       enum AVCodecID codec_id, int width, int height)
{
    AVCodecContext *c;
    int i;

    /* find the encoder */
    *codec = avcodec_find_encoder(codec_id);
    if (!(*codec)) {
        fprintf(stderr, "Could not find encoder for '%s'\n",
                avcodec_get_name(codec_id));
        exit(1);
    }

    ost->tmp_pkt = av_packet_alloc();
    if (!ost->tmp_pkt) {
        fprintf(stderr, "Could not allocate AVPacket\n");
        exit(1);
    }

    ost->st = avformat_new_stream(oc, NULL);
    if (!ost->st) {
        fprintf(stderr, "Could not allocate stream\n");
        exit(1);
    }
    ost->st->id = oc->nb_streams-1;
    c = avcodec_alloc_context3(*codec);
    if (!c) {
        fprintf(stderr, "Could not alloc an encoding context\n");
        exit(1);
    }
    ost->enc = c;
    
    c->codec_id = codec_id;
    //---c->bit_rate = 400000;
    /* Resolution must be a multiple of two. */
    c->width    = width;
    c->height   = height;
    /* timebase: This is the fundamental unit of time (in seconds) in terms
     * of which frame timestamps are represented. For fixed-fps content,
     * timebase should be 1/framerate and timestamp increments should be
     * identical to 1. */

    //ost->st->time_base = (AVRational){ 1, STREAM_FRAME_RATE };
    //c->time_base       = ost->st->time_base;
    c->time_base       = (AVRational){ 1, STREAM_FRAME_RATE };
    
    //---c->gop_size      = 12; /* emit one intra frame every twelve frames at most */
    c->pix_fmt       = STREAM_PIX_FMT;
    if (c->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
	/* just for testing, we also add B-frames */
	c->max_b_frames = 2;
    }
    if (c->codec_id == AV_CODEC_ID_MPEG1VIDEO) {
	/* Needed to avoid using macroblocks in which some coeffs overflow.
	 * This does not happen with normal video, it just happens here as
	 * the motion of the chroma plane does not match the luma plane. */
	c->mb_decision = 2;
    }
    
    /* Some formats want stream headers to be separate. */
    if (oc->oformat->flags & AVFMT_GLOBALHEADER)
        c->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
}

static AVFrame *alloc_frame(enum AVPixelFormat pix_fmt, int width, int height)
{
    AVFrame *frame;
    int ret;
    
    frame = av_frame_alloc();
    if (!frame)
        return NULL;
    
    frame->format = pix_fmt;
    frame->width  = width;
    frame->height = height;
    
    /* allocate the buffers for the frame data */
    ret = av_frame_get_buffer(frame, 0);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate frame data.\n");
        exit(1);
    }
    
    return frame;
}

static void open_video(AVFormatContext *oc, const AVCodec *codec,
                       OutputStream *ost, AVDictionary *opt_arg)
{
    int ret;
    AVCodecContext *c = ost->enc;
    AVDictionary *opt = NULL;

    av_dict_copy(&opt, opt_arg, 0);
    //    av_dict_set(&opt, "vprofile", "baseline", 0);
    
    /* open the codec */
    ret = avcodec_open2(c, codec, &opt);
    av_dict_free(&opt);
    if (ret < 0) {
        fprintf(stderr, "Could not open video codec: %s\n", av_err2str(ret));
        exit(1);
    }

    /* allocate and init a re-usable frame */
    ost->frame = alloc_frame(c->pix_fmt, c->width, c->height);
    if (!ost->frame) {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }

    /* copy the stream parameters to the muxer */
    ret = avcodec_parameters_from_context(ost->st->codecpar, c);
    if (ret < 0) {
        fprintf(stderr, "Could not copy the stream parameters\n");
        exit(1);
    }
}






// OriginBottomLeft: transform (x,y) coordinates from the space into raylib Vector2 coordinates with origin in the bottom-left part of the window (instead of the top-left, as default) 
Vector2 OBLrec(double sq, double x, double y){ 
    return (Vector2){(x*sq),-1*(sq+(y*sq))};
}

Vector2 OBLhexodd(double sq, double x, double y){
    double ap =  sq-(sqrt(3)/2)*sq; // apothem for hex grids
    return (Vector2){sq/2+(x*sq),-1*(sq/2+(y*(sq-ap)))};
}

Vector2 OBLhexeven(double sq, double x, double y){
    double ap =  sq-(sqrt(3)/2)*sq; // apothem for hex grids
    return (Vector2){sq/2+(x*sq)+sq/2,-1*(sq/2+(y*(sq-ap)))};
}

int DrawVectorodd(double sq, double x, double y, double vx, double vy, double color){
    double ap =  sq-(sqrt(3)/2)*sq; // apothem for hex grids
    double vm = sqrt(vx*vx+vy*vy);
    double vecx = vx;
    double vecy = vy;

    if (vm > 1){ // limit vector to squaresize
	vecy = (vecy/vm);
	vecx = (vecx/vm);
    }

    vecx = (vx/vm);
    vecy = (vy/vm);

    vm = (sq/25)*vm;
    
    /*DrawLineEx((Vector2){(x*sq)+sq/2,-1*(y*(sq-ap)+sq/2)},
	       (Vector2){sq/2+(x*sq)+(vecy*(sq/2)),-1*(sq/2+(y*(sq-ap))+(vecx*(sq/2)))},
	       vm*2,
	       GetColor((int)color));*/

    DrawLineEx((Vector2){(x*sq)+sq/2,-1*(y*(sq-ap)+sq/2)},
	       (Vector2){(x*sq)+sq/2+(vecx*(sq/2)),-1*(sq/2+(y*(sq-ap))+(vecy*(sq/2)))},
	       vm*4,
	       GetColor((int)color));
    

    //DrawCircle(s->sq/2+(i*s->sq)+(vy*(s->sq/2)),-1*(s->sq/2+(j*(s->sq-ap))+(vx*(s->sq/2))),(vm*4)/s->sq,GetColor((int)vcolor));

    return 0;
}


int DrawVectoreven(double sq, double x, double y, double vx, double vy, double color){
    double ap =  sq-(sqrt(3)/2)*sq; // apothem for hex grids
    double vm = sqrt(vx*vx+vy*vy);
    double vecx = vx;
    double vecy = vy;

    if (vm > 1){ // limit vector to squaresize
	vecy = (vecy/vm);
	vecx = (vecx/vm);
    }
    vm = (sq/25)*vm;

    vecx = (vx/vm);
    vecy = (vy/vm);
    
    /*DrawLineEx((Vector2){sq/2+(sq/2)+(x*sq),-1*(sq/2+(y*(sq-ap)))},
	       (Vector2){sq/2+(sq/2)+(x*sq)+(vecy*(sq/2)),-1*(sq/2+(y*(sq-ap))+(vecx*(sq/2)))},
	       vm*2,GetColor((int)color));
    */
    DrawLineEx((Vector2){sq/2+(sq/2)+(x*sq),-1*(sq/2+(y*(sq-ap)))},
	       (Vector2){sq/2+(sq/2)+(x*sq)+(vecx*(sq/2)),-1*(sq/2+(y*(sq-ap))+(vecy*(sq/2)))},
	       vm*4,
	       GetColor((int)color));

    
    //DrawCircle(s->sq/2+(s->sq/2)+(i*s->sq)+(vy*(s->sq/2)),-1*(s->sq/2+(j*(s->sq-ap))+(vx*(s->sq/2))),(vm*4)/s->sq,GetColor((int)vcolor));

    return 0;
}

static void log_packet(const AVFormatContext *fmt_ctx, const AVPacket *pkt)
{
    AVRational *time_base = &fmt_ctx->streams[pkt->stream_index]->time_base;

    printf("pts:%s pts_time:%s dts:%s dts_time:%s duration:%s duration_time:%s stream_index:%d\n",
           av_ts2str(pkt->pts), av_ts2timestr(pkt->pts, time_base),
           av_ts2str(pkt->dts), av_ts2timestr(pkt->dts, time_base),
           av_ts2str(pkt->duration), av_ts2timestr(pkt->duration, time_base),
           pkt->stream_index);
}

static int write_frame(AVFormatContext *fmt_ctx, AVCodecContext *c, AVStream *st, AVFrame *frame, AVPacket *pkt)
{
    int ret;

    //printf("WRITE FRAME\n");
    
    // send the frame to the encoder
    ret = avcodec_send_frame(c, frame);
    if (ret < 0) {
	fprintf(stderr, "Error sending a frame to the encoder: %s\n",
                av_err2str(ret));
        exit(1);
    }
    while (ret >= 0) {
        ret = avcodec_receive_packet(c, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF){
	    break;
        }else if (ret < 0) {
            fprintf(stderr, "Error encoding a frame: %s\n", av_err2str(ret));
            exit(1);
        }
	/* rescale output packet timestamp values from codec to stream timebase */
	av_packet_rescale_ts(pkt, c->time_base, st->time_base);
	pkt->stream_index = st->index;
	
	/* Write the compressed frame to the media file. */
	//log_packet(fmt_ctx, pkt);
	ret = av_interleaved_write_frame(fmt_ctx, pkt);
	/* pkt is now blank (av_interleaved_write_frame() takes ownership of
	 * its contents and resets pkt), so that no unreferencing is necessary.
	 * This would be different if one used av_write_frame(). */
	if (ret < 0) {
	    fprintf(stderr, "Error while writing output packet: %s\n", av_err2str(ret));
	    exit(1);
	}
    }
    
    return ret == AVERROR_EOF ? 1 : 0;
}


static AVFrame *get_video_frame(OutputStream *ost)
{
    AVCodecContext *c = ost->enc;
    Image sc = LoadImageFromScreen(); // take screenshot
    //const uint8_t * const inData[1] = { sc.data }; // RGBA data from Image
    int inLinesize[1] = { 4*sc.width }; // RGBA stride
    
    //printf("GET VIDEO FRAME\n");
    
    /* check if we want to generate more frames */
    //if (av_compare_ts(ost->next_pts, c->time_base, SIM_TIME, (AVRational){ 1, 1 }) > 0)
    //    return NULL;
    
    /* when we pass a frame to the encoder, it may keep a reference to it
     * internally; make sure we do not overwrite it here */
    if (av_frame_make_writable(ost->frame) < 0)
        exit(1);
    
    // Convert from RGBA to YUV420P
    if (!ost->sws_ctx) {
	ost->sws_ctx = sws_getContext(c->width, c->height, AV_PIX_FMT_RGBA,
				      c->width, c->height, AV_PIX_FMT_YUV420P,
				      0 , NULL, NULL, NULL);
	if (!ost->sws_ctx) {
	    fprintf(stderr,
		    "Could not initialize the conversion context\n");
	    exit(1);
	}
    }
    sws_scale(ost->sws_ctx, (const uint8_t * const *) &(sc.data),
          inLinesize, 0, c->height, ost->frame->data,
    	      ost->frame->linesize);
    

    
    ost->frame->pts = ost->next_pts++;

    return ost->frame;
}

// double COLOR display (void* space, int x,int y, int z, double* SCALARVALUE, double* VECTOR_X, double* VECTOR_Y, double* VECTOR_Z)
int CS_Plot(void* animation){
    Animation* a;
    CellSpace *s;
    Cell *cell;
    int i,j,k;
    double vm,vcolor;
    double ap;
    double VAL;
    double COLOR;
    double VX,VY,VZ;
    
    //    ModelicaFormatMessage("PLOT\n");
    
    a = (Animation*) animation;
    s = (CellSpace*) a->space;
    // 1D - plot animation for new states
    //printf("NDIMS = %d\n",a->ndims);

    if(a->display == NULL){
	ModelicaFormatMessage("PLOT ERROR: Display function not found\n");
	exit(-2);
    }
    
    if(s->ndims == 1){
	BeginDrawing();
	ClearBackground(RAYWHITE);
	BeginMode2D(a->camera2);
	if(a->storehistory){
	    a->n_hist++;
	    a->hist = (double**)realloc((double**)a->hist,sizeof(double*)*a->n_hist);
	    a->hist[a->n_hist-1] = (double*)malloc(sizeof(double)*a->wX);
	    if (a->hist == NULL) exit(-1);
	    // store current states in history    
	    for (i=0;i<a->wX;i++){
		COLOR = a->display(a->space,i,0,0,&VAL,&VX,&VY,&VZ);
		a->hist[a->n_hist-1][i] = COLOR;
	    }
	}
	// PLOT history, including current state
	for(i=0;i<a->n_hist-1;i++){
	    for(j=0;j<a->wX;j++){
		DrawRectangleV(OBLrec(a->sq,j,i), (Vector2){a->sq,a->sq}, GetColor((int)a->hist[i][j]));
	    }
	}
	EndMode2D();
	EndDrawing();
    }
    // 2D - plot animation for new states
    if(s->ndims == 2){
	BeginDrawing();
	ClearBackground(RAYWHITE);
	BeginMode2D(a->camera2);
	//	  ModelicaFormatMessage("[");
	ap = a->sq-(sqrt(3)/2)*a->sq; // apothem for hex grids
	for (i=0;i<a->wX;i++){
	    for(j=0;j<a->wY;j++){
		cell = s->M[i][j][a->wZ-1];
		if (cell != NULL){
		    // cell present in space, draw state.
		    COLOR = a->display(a->space,i,j,0,&VAL,&VX,&VY,&VZ);
		    if (s->hex){ // hexagonal lattice
			if(a->plot_vector){ // vector field
			    if(!(j%2)){ //odd rows
				DrawPoly(OBLhexodd(a->sq,i,j), 6, (a->sq/2), 0, WHITE);
				DrawVectorodd(a->sq,i,j,VX,VY,COLOR);
			    }else{ // even rows
				DrawPoly(OBLhexeven(a->sq,i,j), 6, (a->sq/2) , 0,WHITE);
				DrawVectoreven(a->sq,i,j,VX,VY,COLOR);
			    }
			}else{
			    if(!(j%2))
				DrawPoly(OBLhexodd(a->sq,i,j), 6, (a->sq/2), 0, GetColor((int)COLOR));
			    else
				DrawPoly(OBLhexeven(a->sq,i,j), 6, (a->sq/2) , 0, GetColor((int)COLOR));
			}
		    }else{ // square lattice
			if(a->plot_vector){
			    DrawVectorodd(a->sq,i,j,VX,VY,COLOR);
			}else{
			    DrawRectangleV(OBLrec(a->sq,i,j), (Vector2){a->sq,a->sq}, GetColor((int)COLOR));
			}
		    }
		}else{// cell not present, print default
		    if(s->hex)
			if(!(j%2))
			    DrawPoly(OBLhexodd(a->sq,i,j), 6, (a->sq/2), 0, BLANK);
			else
			    DrawPoly(OBLhexeven(a->sq,i,j), 6, (a->sq/2), 0, BLANK);
		    else
			DrawRectangleV(OBLrec(a->sq,i,j), (Vector2){a->sq,a->sq}, BLANK);
		}
	    }
	}
	usleep(a->displayDelay);
	EndMode2D();
	EndDrawing();
    }
    
    // 3D - plot animation for new states
    if(s->ndims == 3){
	// Update
	//----------------------------------------------------------------------------------
	UpdateCamera(&a->camera3, CAMERA_THIRD_PERSON);
	
	if (IsKeyDown('Z')) a->camera3.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	//----------------------------------------------------------------------------------
	
	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();
	
	ClearBackground(RAYWHITE);
	
	BeginMode3D(a->camera3);
	
	// Paint 3D Matrix
	for(i=0;i<a->wX;i++){
	    for(j=0;j<a->wY;j++){
		for(k=0;k<a->wZ;k++){
		    cell = s->M[i][j][k];
		    COLOR = a->display(a->space,i,j,k,&VAL,&VX,&VY,&VZ);
		    if (cell != NULL){
			// cell present in space, print state.
			DrawCubeV((Vector3){i*a->sq,j*a->sq,k*a->sq},(Vector3){a->sq,a->sq,a->sq},GetColor((int)COLOR));
		    }else{// cell not present, print default
			DrawCubeV((Vector3){i*a->sq,j*a->sq,k*a->sq},(Vector3){a->sq,a->sq,a->sq},BLANK);
			
		    }
		}
	    }
	}
	EndMode3D();
	usleep(a->displayDelay);
	EndDrawing();
    }

    // RECORD ANIMATION VIDEO
    if (a->save_video){
	WaitTime(0.0001);
	
	//int encode_video = 1;
	//while (encode_video) {
	    /* select the stream to encode */
	//printf("VIDEO_ST ENC = %p\n",a->video_st.st);
	write_frame(a->oc, a->video_st.enc, a->video_st.st, get_video_frame(&a->video_st), a->video_st.tmp_pkt);
	//}
    }
    
    //    ModelicaFormatMessage("END PLOT\n");
    return 1;
}

static void close_stream(AVFormatContext *oc, OutputStream *ost)
{
    avcodec_free_context(&ost->enc);
    av_frame_free(&ost->frame);
    //av_frame_free(&ost->tmp_frame);
    av_packet_free(&ost->tmp_pkt);
    sws_freeContext(ost->sws_ctx);
    //  swr_free(&ost->swr_ctx);
}





// Function used to create and populate a new cellular space. It is used as constructor for the external object, that is returned as a void pointer
void* CS_CreateAnimation(int winWidth, int winHeight, int WX, int WY, int WZ, double displayDelay, int vector, int save_video, const char* name){
    int i,j,k;
    int wrapped;
    int res;
    int screenWidth;
    int screenHeight;
    Animation *a;

    //    ModelicaFormatMessage("CREATE ANIMATION\n");

    a = (Animation *)malloc(sizeof(Animation));

    a->wX = WX;
    a->wY = WY;
    a->wZ = WZ; 
    a->sq = 0; 
    a->save_video = save_video;
    a->displayDelay = displayDelay; 
    a->plot_vector = vector;
    a->display = NULL;

    a->pts = 0;
    a->storehistory = WY > 0;
    a->hist = NULL;
    a->n_hist = 0;
    a->video_st.sws_ctx = NULL;
    a->video_st.next_pts = 0;
    a->video_codec = NULL;
    a->oc = NULL;
    a->fmt = NULL;

    // CREATE RAYLIB WINDOW
    if (WZ == 1) {  // 1D or 2D animation
	a->sq = (winWidth-(2*OFFSET))/(double)WX;
	a->camera2.target = (Vector2){0.0,0.0};
	a->camera2.offset = (Vector2){0,winHeight};
	a->camera2.rotation = 0.0;
	a->camera2.zoom = 1.0;
	InitWindow(winWidth, winHeight,name);
    }else{ // 3D animation
	a->sq = (winWidth/WX)/50.0f;
	//ModelicaFormatMessage("SQ = %lf\n",a->sq);
	InitWindow(winWidth, winHeight,name);
	a->camera3.position = (Vector3){2*WX, 2*WY, 2*WZ}; // Camera3 position
	a->camera3.target = (Vector3){ 0.0, 0.0, 0.0 };      // Camera3 looking at point
	a->camera3.up = (Vector3){ 0.0, a->sq, 0.0 };          // Camera3 up vector (rotation towards target)
	a->camera3.fovy = 45.0;                                // Camera3 field-of-view Y
	a->camera3.projection = CAMERA_ORTHOGRAPHIC;//CAMERA_PERSPECTIVE;             // Camera3 projection type
	DisableCursor();                    // Limit cursor to relative movement inside the window
    }
    
    // INITIALIZE VIDEO RECORDING
    if (save_video){
	a->save_video = 1;
	int ret;
	int i;
	
	AVDictionary *opt = NULL;
	
	char filename[256];
       	sprintf(filename,"%s_video_%ld.mp4",name,time(NULL));
	//ModelicaFormatMessage("VIDEO FILENAME = %s\n",filename);
	
	/* allocate the output media context */
	avformat_alloc_output_context2(&a->oc, NULL, NULL, filename);
	if (!a->oc) {
	    printf("Could not deduce output format from file extension: using MPEG.\n");
	    avformat_alloc_output_context2(&a->oc, NULL, "mpeg", filename);
	}
	if (!a->oc)
	    return NULL;
	
	a->fmt = a->oc->oformat;
	/* Add video stream using the default format codecs
	 * and initialize the codecs. */
	if (a->fmt->video_codec != AV_CODEC_ID_NONE) {
	    add_stream(&a->video_st, a->oc, &a->video_codec, a->fmt->video_codec,winWidth,winHeight);
	    /* Now that all the parameters are set, we can open the audio and
	     * video codecs and allocate the necessary encode buffers. */
	    open_video(a->oc, a->video_codec, &a->video_st, opt);
	}
	
	av_dump_format(a->oc, 0, filename, 1);
	
	/* open the output file, if needed */
	if (!(a->fmt->flags & AVFMT_NOFILE)) {
	    ret = avio_open(&a->oc->pb, filename, AVIO_FLAG_WRITE);
	    if (ret < 0) {
		fprintf(stderr, "Could not open '%s': %s\n", filename,
			av_err2str(ret));
		return NULL;
	    }
	}
	
	/* Write the stream header, if any. */
	ret = avformat_write_header(a->oc, &opt);
	if (ret < 0) {
	    fprintf(stderr, "Error occurred when opening output file: %s\n",
		    av_err2str(ret));
	    return NULL;
	}
	
    }
    
    //    ModelicaFormatMessage("END CREATE ANIMATION\n");
    return (void *)a;
}

// double COLOR display (void* space, int x,int y, int z, double* VMODULE, double* VECTOR_X, double* VECTOR_Y, double* VECTOR_Z)
int CS_SetDisplay(void* anim, void* space, double (*display)(void*,int,int,int,double*,double*,double*,double*)){
    Animation *a;

    //    ModelicaFormatMessage("SET DISPLAY\n");
    
    a = (Animation*) anim;
    a->space = space;
    a->display = display;
    
    //ModelicaFormatMessage("END SET DISPLAY\n");

    return 0;
}


///void* CS_InitAnimation(void* animation, int winWidth, int winHeight, int wX, int wY, int wZ, int vector, int displayDelay, const char *name, int save_video){
///    CellSpace* s;
///    //int screenWidth, screenHeight;
///    int cellsize;
///    Animation *a;
///    
///    //printf("CS_plot\n");
///
///    ModelicaFormatMessage("INIT ANIMATION\n");
///    
///    s = (CellSpace*) space;
///
///    s->plot_vector = vector;
///    s->wX = wX;
///    s->wY = wY;
///    s->wZ = wZ;
///
///    s->displayDelay = displayDelay;
///    s->plot_animation = 1;
///    s->storehistory = wY > 0;
///    
///    if (s->ndims == 1 || s->ndims == 2){ // 1D or 2D animation using raylib
///	//screenWidth = fmin((wX*SQUARESIZE)+2*OFFSET,winMaxWidth);
///	//screenHeight = fmin((wY*SQUARESIZE)+2*OFFSET,winMaxHeight); 
///	s->sq = (winWidth-(2*OFFSET))/(double)wX;
///	s->camera2.target = (Vector2){0.0,0.0};
///	s->camera2.offset = (Vector2){0,winHeight};
///	s->camera2.rotation = 0.0;
///	s->camera2.zoom = 1.0;
///	InitWindow(winWidth, winHeight,name);
///	//SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second	
///    }else if (s->ndims == 3){
///	s->sq = (winWidth/wX)/50.0f;
///	//ModelicaFormatMessage("SQ = %lf\n",s->sq);
///	//screenWidth = winMaxWidth;
///	//screenHeight = winMaxHeight;
///	InitWindow(winWidth, winHeight,name);
///	// s->camera3.position = (Vector3){s->squaresize*10, s->squaresize*10, s->squaresize*10 }; // Camera3 position
///	s->camera3.position = (Vector3){2*wX, 2*wY, 2*wZ}; // Camera3 position
///	//	s->camera3.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera3 position
///	s->camera3.target = (Vector3){ 0.0, 0.0, 0.0 };      // Camera3 looking at point
///	s->camera3.up = (Vector3){ 0.0, s->sq, 0.0 };          // Camera3 up vector (rotation towards target)
///	s->camera3.fovy = 45.0;                                // Camera3 field-of-view Y
///	s->camera3.projection = CAMERA_ORTHOGRAPHIC;//CAMERA_PERSPECTIVE;             // Camera3 projection type
///	DisableCursor();                    // Limit cursor to relative movement inside the window
///	//SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second	
///    }
///
///    // INITIALIZE VIDEO RECORDING
///    if (save_video){
///	s->save_video = 1;
///	int ret;
///	int i;
///    
///	AVDictionary *opt = NULL;
///	 
///	char filename[256];
///       	sprintf(filename,"%s_video_%ld.mp4",name,time(NULL));
///	ModelicaFormatMessage("VIDEO FILENAME = %s\n",filename);
///
///	 /* allocate the output media context */
///	avformat_alloc_output_context2(&s->oc, NULL, NULL, filename);
///	if (!s->oc) {
///	    printf("Could not deduce output format from file extension: using MPEG.\n");
///	    avformat_alloc_output_context2(&s->oc, NULL, "mpeg", filename);
///	}
///	if (!s->oc)
///	    return 1;
///
///	s->fmt = s->oc->oformat;
///	/* Add video stream using the default format codecs
///	 * and initialize the codecs. */
///	if (s->fmt->video_codec != AV_CODEC_ID_NONE) {
///	    add_stream(&s->video_st, s->oc, &s->video_codec, s->fmt->video_codec,winWidth,winHeight);
///	    /* Now that all the parameters are set, we can open the audio and
///	     * video codecs and allocate the necessary encode buffers. */
///	    open_video(s->oc, s->video_codec, &s->video_st, opt);
///	}
///
///	av_dump_format(s->oc, 0, filename, 1);
///
///	/* open the output file, if needed */
///	if (!(s->fmt->flags & AVFMT_NOFILE)) {
///	    ret = avio_open(&s->oc->pb, filename, AVIO_FLAG_WRITE);
///	    if (ret < 0) {
///		fprintf(stderr, "Could not open '%s': %s\n", filename,
///			av_err2str(ret));
///		return 1;
///	    }
///	}
///
///	/* Write the stream header, if any. */
///	ret = avformat_write_header(s->oc, &opt);
///	if (ret < 0) {
///	    fprintf(stderr, "Error occurred when opening output file: %s\n",
///		    av_err2str(ret));
///	    return 1;
///	}
///
///    }
///    ModelicaFormatMessage("END INIT ANIMATION\n");
///}



int CS_DeleteAnimation(void* anim){
    Animation *a;
    int i,j,k;
    //uint8_t endcode[] = { 0, 0, 1, 0xb7 };
    
    a = (Animation *)anim;
    
    //ModelicaFormatMessage("CS_Delete\n");
    
    // flush encoder if save_video and end video
    if (a->save_video){
	// wait codec to return all frames
	while (!write_frame(a->oc, a->video_st.enc, a->video_st.st, NULL, a->video_st.tmp_pkt));
	
	av_write_trailer(a->oc);
	//      encode(a->c,NULL,a->pkt,a->f);
	//      if (a->codec->id == AV_CODEC_ID_MPEG1VIDEO || a->codec->id == AV_CODEC_ID_MPEG2VIDEO)
	//	  fwrite(endcode, 1, sizeof(endcode), a->f);
	//fclose(a->f);
	close_stream(a->oc, &a->video_st);
	avio_closep(&a->oc->pb);
	/* free the stream */
	avformat_free_context(a->oc);
	a->save_video = 0;
    }    
    a->storehistory = 0;
    
    // Wait for animation window to close
    while(!WindowShouldClose())
	CS_Plot(anim);
    CloseWindow();
    
///    // free memory
///    for(i=0;i<s->X;i++){
///	for(j=0;j<s->Y;j++){
///	    for(k=0;k<s->Z;k++){
///		cell = s->M[i][j][k];
///		s->M[i][j][k] = NULL;
///		free(cell);
///	    }
///	    free(s->M[i][j]);
///	}
///	free(s->M[i]);
///    }
///    free(s->M);
///    free(s->A);
///    free(s->neighborhood);
///    if(s->hex)
///	free(s->oddneighborhood);
///
    free(a);
    return 1;
}


#endif
