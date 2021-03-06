#include "FFmpeg.hpp"


bool FFmpeg::_hasBeenInit = globalInit();

bool FFmpeg::globalInit()
{
        //	av_log_set_level( AV_LOG_QUIET );
        av_log_set_level( AV_LOG_ERROR );
        //	av_log_set_level( AV_LOG_WARNING );
        //	av_log_set_level( AV_LOG_DEBUG );
        av_register_all();
        return true;
}

#define CASE_RETURN_STRING( e ) case e: return # e

const std::string FFmpeg::ffmpegError_toString( int error )
{
        switch( error )
        {
#if LIBAVCODEC_VERSION_MAJOR > 52
                case AVERROR_BSF_NOT_FOUND:
                        return "Bitstream filter not found";
                case AVERROR_DECODER_NOT_FOUND:
                        return "Decoder not found";
                case AVERROR_DEMUXER_NOT_FOUND:
                        return "Demuxer not found";
                case AVERROR_ENCODER_NOT_FOUND:
                        return "Encoder not found";
                case AVERROR_EXIT:
                        return "Immediate exit was requested; the called function should not be restarted";
                case AVERROR_FILTER_NOT_FOUND:
                        return "Filter not found";
                case AVERROR_MUXER_NOT_FOUND:
                        return "Muxer not found";
                case AVERROR_OPTION_NOT_FOUND:
                        return "Option not found";
                case AVERROR_PROTOCOL_NOT_FOUND:
                        return "Protocol not found";
                case AVERROR_STREAM_NOT_FOUND:
                        return "Stream not found";
#endif
                case AVERROR_EOF:
                        return "End of file";
                case AVERROR_INVALIDDATA:
                        return "Invalid data found when processing input";
                case AVERROR_PATCHWELCOME:
                        return "Not yet implemented in FFmpeg, patches welcome";
                default:
                        return "unknown error";
        }
}

const std::string FFmpeg::codecID_toString( const CodecID codec_id )
{
        switch( codec_id )
        {
                CASE_RETURN_STRING( CODEC_ID_NONE );
                CASE_RETURN_STRING( CODEC_ID_MPEG1VIDEO );
                CASE_RETURN_STRING( CODEC_ID_MPEG2VIDEO );
                CASE_RETURN_STRING( CODEC_ID_MPEG2VIDEO_XVMC );
                CASE_RETURN_STRING( CODEC_ID_H261 );
                CASE_RETURN_STRING( CODEC_ID_H263 );
                CASE_RETURN_STRING( CODEC_ID_RV10 );
                CASE_RETURN_STRING( CODEC_ID_RV20 );
                CASE_RETURN_STRING( CODEC_ID_MJPEG );
                CASE_RETURN_STRING( CODEC_ID_MJPEGB );
                CASE_RETURN_STRING( CODEC_ID_LJPEG );
                CASE_RETURN_STRING( CODEC_ID_SP5X );
                CASE_RETURN_STRING( CODEC_ID_JPEGLS );
                CASE_RETURN_STRING( CODEC_ID_MPEG4 );
                CASE_RETURN_STRING( CODEC_ID_RAWVIDEO );
                CASE_RETURN_STRING( CODEC_ID_MSMPEG4V1 );
                CASE_RETURN_STRING( CODEC_ID_MSMPEG4V2 );
                CASE_RETURN_STRING( CODEC_ID_MSMPEG4V3 );
                CASE_RETURN_STRING( CODEC_ID_WMV1 );
                CASE_RETURN_STRING( CODEC_ID_WMV2 );
                CASE_RETURN_STRING( CODEC_ID_H263P );
                CASE_RETURN_STRING( CODEC_ID_H263I );
                CASE_RETURN_STRING( CODEC_ID_FLV1 );
                CASE_RETURN_STRING( CODEC_ID_SVQ1 );
                CASE_RETURN_STRING( CODEC_ID_SVQ3 );
                CASE_RETURN_STRING( CODEC_ID_DVVIDEO );
                CASE_RETURN_STRING( CODEC_ID_HUFFYUV );
                CASE_RETURN_STRING( CODEC_ID_CYUV );
                CASE_RETURN_STRING( CODEC_ID_H264 );
                CASE_RETURN_STRING( CODEC_ID_VP3 );
                CASE_RETURN_STRING( CODEC_ID_THEORA );
                CASE_RETURN_STRING( CODEC_ID_ASV1 );
                CASE_RETURN_STRING( CODEC_ID_ASV2 );
                CASE_RETURN_STRING( CODEC_ID_FFV1 );
                CASE_RETURN_STRING( CODEC_ID_4XM );
                CASE_RETURN_STRING( CODEC_ID_VCR1 );
                CASE_RETURN_STRING( CODEC_ID_CLJR );
                CASE_RETURN_STRING( CODEC_ID_MDEC );
                CASE_RETURN_STRING( CODEC_ID_ROQ );
                CASE_RETURN_STRING( CODEC_ID_INTERPLAY_VIDEO );
                CASE_RETURN_STRING( CODEC_ID_XAN_WC3 );
                CASE_RETURN_STRING( CODEC_ID_XAN_WC4 );
                CASE_RETURN_STRING( CODEC_ID_RPZA );
                CASE_RETURN_STRING( CODEC_ID_CINEPAK );
                CASE_RETURN_STRING( CODEC_ID_WS_VQA );
                CASE_RETURN_STRING( CODEC_ID_MSRLE );
                CASE_RETURN_STRING( CODEC_ID_MSVIDEO1 );
                CASE_RETURN_STRING( CODEC_ID_IDCIN );
                CASE_RETURN_STRING( CODEC_ID_8BPS );
                CASE_RETURN_STRING( CODEC_ID_SMC );
                CASE_RETURN_STRING( CODEC_ID_FLIC );
                CASE_RETURN_STRING( CODEC_ID_TRUEMOTION1 );
                CASE_RETURN_STRING( CODEC_ID_VMDVIDEO );
                CASE_RETURN_STRING( CODEC_ID_MSZH );
                CASE_RETURN_STRING( CODEC_ID_ZLIB );
                CASE_RETURN_STRING( CODEC_ID_QTRLE );
                CASE_RETURN_STRING( CODEC_ID_SNOW );
                CASE_RETURN_STRING( CODEC_ID_TSCC );
                CASE_RETURN_STRING( CODEC_ID_ULTI );
                CASE_RETURN_STRING( CODEC_ID_QDRAW );
                CASE_RETURN_STRING( CODEC_ID_VIXL );
                CASE_RETURN_STRING( CODEC_ID_QPEG );
#if LIBAVCODEC_VERSION_MAJOR < 53
                CASE_RETURN_STRING( CODEC_ID_XVID ); // removed from ffmpeg
#endif
                CASE_RETURN_STRING( CODEC_ID_PNG );
                CASE_RETURN_STRING( CODEC_ID_PPM );
                CASE_RETURN_STRING( CODEC_ID_PBM );
                CASE_RETURN_STRING( CODEC_ID_PGM );
                CASE_RETURN_STRING( CODEC_ID_PGMYUV );
                CASE_RETURN_STRING( CODEC_ID_PAM );
                CASE_RETURN_STRING( CODEC_ID_FFVHUFF );
                CASE_RETURN_STRING( CODEC_ID_RV30 );
                CASE_RETURN_STRING( CODEC_ID_RV40 );
                CASE_RETURN_STRING( CODEC_ID_VC1 );
                CASE_RETURN_STRING( CODEC_ID_WMV3 );
                CASE_RETURN_STRING( CODEC_ID_LOCO );
                CASE_RETURN_STRING( CODEC_ID_WNV1 );
                CASE_RETURN_STRING( CODEC_ID_AASC );
                CASE_RETURN_STRING( CODEC_ID_INDEO2 );
                CASE_RETURN_STRING( CODEC_ID_FRAPS );
                CASE_RETURN_STRING( CODEC_ID_TRUEMOTION2 );
                CASE_RETURN_STRING( CODEC_ID_BMP );
                CASE_RETURN_STRING( CODEC_ID_CSCD );
                CASE_RETURN_STRING( CODEC_ID_MMVIDEO );
                CASE_RETURN_STRING( CODEC_ID_ZMBV );
                CASE_RETURN_STRING( CODEC_ID_AVS );
                CASE_RETURN_STRING( CODEC_ID_SMACKVIDEO );
                CASE_RETURN_STRING( CODEC_ID_NUV );
                CASE_RETURN_STRING( CODEC_ID_KMVC );
                CASE_RETURN_STRING( CODEC_ID_FLASHSV );
                CASE_RETURN_STRING( CODEC_ID_CAVS );
                CASE_RETURN_STRING( CODEC_ID_JPEG2000 );
                CASE_RETURN_STRING( CODEC_ID_VMNC );
                CASE_RETURN_STRING( CODEC_ID_VP5 );
                CASE_RETURN_STRING( CODEC_ID_VP6 );
                CASE_RETURN_STRING( CODEC_ID_VP6F );
                CASE_RETURN_STRING( CODEC_ID_TARGA );
                CASE_RETURN_STRING( CODEC_ID_DSICINVIDEO );
                CASE_RETURN_STRING( CODEC_ID_TIERTEXSEQVIDEO );
                CASE_RETURN_STRING( CODEC_ID_TIFF );
                CASE_RETURN_STRING( CODEC_ID_GIF );
                CASE_RETURN_STRING( CODEC_ID_FFH264 );
                CASE_RETURN_STRING( CODEC_ID_DXA );
                CASE_RETURN_STRING( CODEC_ID_DNXHD );
                CASE_RETURN_STRING( CODEC_ID_THP );
                CASE_RETURN_STRING( CODEC_ID_SGI );
                CASE_RETURN_STRING( CODEC_ID_C93 );
                CASE_RETURN_STRING( CODEC_ID_BETHSOFTVID );
                CASE_RETURN_STRING( CODEC_ID_PTX );
                CASE_RETURN_STRING( CODEC_ID_TXD );
                CASE_RETURN_STRING( CODEC_ID_VP6A );
                CASE_RETURN_STRING( CODEC_ID_AMV );
                CASE_RETURN_STRING( CODEC_ID_VB );
                CASE_RETURN_STRING( CODEC_ID_PCX );
                CASE_RETURN_STRING( CODEC_ID_SUNRAST );
                CASE_RETURN_STRING( CODEC_ID_INDEO4 );
                CASE_RETURN_STRING( CODEC_ID_INDEO5 );
                CASE_RETURN_STRING( CODEC_ID_MIMIC );
                CASE_RETURN_STRING( CODEC_ID_RL2 );
                CASE_RETURN_STRING( CODEC_ID_8SVX_EXP );
                CASE_RETURN_STRING( CODEC_ID_8SVX_FIB );
                CASE_RETURN_STRING( CODEC_ID_ESCAPE124 );
                CASE_RETURN_STRING( CODEC_ID_DIRAC );
                CASE_RETURN_STRING( CODEC_ID_BFI );
                CASE_RETURN_STRING( CODEC_ID_CMV );
                CASE_RETURN_STRING( CODEC_ID_MOTIONPIXELS );
                CASE_RETURN_STRING( CODEC_ID_TGV );
                CASE_RETURN_STRING( CODEC_ID_TGQ );
                CASE_RETURN_STRING( CODEC_ID_TQI );
                CASE_RETURN_STRING( CODEC_ID_PCM_S16LE );
                CASE_RETURN_STRING( CODEC_ID_PCM_S16BE );
                CASE_RETURN_STRING( CODEC_ID_PCM_U16LE );
                CASE_RETURN_STRING( CODEC_ID_PCM_U16BE );
                CASE_RETURN_STRING( CODEC_ID_PCM_S8 );
                CASE_RETURN_STRING( CODEC_ID_PCM_U8 );
                CASE_RETURN_STRING( CODEC_ID_PCM_MULAW );
                CASE_RETURN_STRING( CODEC_ID_PCM_ALAW );
                CASE_RETURN_STRING( CODEC_ID_PCM_S32LE );
                CASE_RETURN_STRING( CODEC_ID_PCM_S32BE );
                CASE_RETURN_STRING( CODEC_ID_PCM_U32LE );
                CASE_RETURN_STRING( CODEC_ID_PCM_U32BE );
                CASE_RETURN_STRING( CODEC_ID_PCM_S24LE );
                CASE_RETURN_STRING( CODEC_ID_PCM_S24BE );
                CASE_RETURN_STRING( CODEC_ID_PCM_U24LE );
                CASE_RETURN_STRING( CODEC_ID_PCM_U24BE );
                CASE_RETURN_STRING( CODEC_ID_PCM_S24DAUD );
                CASE_RETURN_STRING( CODEC_ID_PCM_ZORK );
                CASE_RETURN_STRING( CODEC_ID_PCM_S16LE_PLANAR );
                CASE_RETURN_STRING( CODEC_ID_PCM_DVD );
                CASE_RETURN_STRING( CODEC_ID_PCM_F32BE );
                CASE_RETURN_STRING( CODEC_ID_PCM_F32LE );
                CASE_RETURN_STRING( CODEC_ID_PCM_F64BE );
                CASE_RETURN_STRING( CODEC_ID_PCM_F64LE );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_IMA_QT );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_IMA_WAV );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_IMA_DK3 );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_IMA_DK4 );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_IMA_WS );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_IMA_SMJPEG );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_MS );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_4XM );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_XA );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_ADX );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_EA );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_G726 );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_CT );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_SWF );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_YAMAHA );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_SBPRO_4 );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_SBPRO_3 );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_SBPRO_2 );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_THP );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_IMA_AMV );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_EA_R1 );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_EA_R3 );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_EA_R2 );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_IMA_EA_SEAD );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_IMA_EA_EACS );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_EA_XAS );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_EA_MAXIS_XA );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_IMA_ISS );
                CASE_RETURN_STRING( CODEC_ID_AMR_NB );
                CASE_RETURN_STRING( CODEC_ID_AMR_WB );
                CASE_RETURN_STRING( CODEC_ID_RA_144 );
                CASE_RETURN_STRING( CODEC_ID_RA_288 );
                CASE_RETURN_STRING( CODEC_ID_ROQ_DPCM );
                CASE_RETURN_STRING( CODEC_ID_INTERPLAY_DPCM );
                CASE_RETURN_STRING( CODEC_ID_XAN_DPCM );
                CASE_RETURN_STRING( CODEC_ID_SOL_DPCM );
                CASE_RETURN_STRING( CODEC_ID_MP2 );
                CASE_RETURN_STRING( CODEC_ID_MP3 );
                CASE_RETURN_STRING( CODEC_ID_AAC );
                CASE_RETURN_STRING( CODEC_ID_AC3 );
                CASE_RETURN_STRING( CODEC_ID_DTS );
                CASE_RETURN_STRING( CODEC_ID_VORBIS );
                CASE_RETURN_STRING( CODEC_ID_DVAUDIO );
                CASE_RETURN_STRING( CODEC_ID_WMAV1 );
                CASE_RETURN_STRING( CODEC_ID_WMAV2 );
                CASE_RETURN_STRING( CODEC_ID_MACE3 );
                CASE_RETURN_STRING( CODEC_ID_MACE6 );
                CASE_RETURN_STRING( CODEC_ID_VMDAUDIO );
                CASE_RETURN_STRING( CODEC_ID_SONIC );
                CASE_RETURN_STRING( CODEC_ID_SONIC_LS );
                CASE_RETURN_STRING( CODEC_ID_FLAC );
                CASE_RETURN_STRING( CODEC_ID_MP3ADU );
                CASE_RETURN_STRING( CODEC_ID_MP3ON4 );
                CASE_RETURN_STRING( CODEC_ID_SHORTEN );
                CASE_RETURN_STRING( CODEC_ID_ALAC );
                CASE_RETURN_STRING( CODEC_ID_WESTWOOD_SND1 );
                CASE_RETURN_STRING( CODEC_ID_GSM );
                CASE_RETURN_STRING( CODEC_ID_QDM2 );
                CASE_RETURN_STRING( CODEC_ID_COOK );
                CASE_RETURN_STRING( CODEC_ID_TRUESPEECH );
                CASE_RETURN_STRING( CODEC_ID_TTA );
                CASE_RETURN_STRING( CODEC_ID_SMACKAUDIO );
                CASE_RETURN_STRING( CODEC_ID_QCELP );
                CASE_RETURN_STRING( CODEC_ID_WAVPACK );
                CASE_RETURN_STRING( CODEC_ID_DSICINAUDIO );
                CASE_RETURN_STRING( CODEC_ID_IMC );
                CASE_RETURN_STRING( CODEC_ID_MUSEPACK7 );
                CASE_RETURN_STRING( CODEC_ID_MLP );
                CASE_RETURN_STRING( CODEC_ID_GSM_MS );
                CASE_RETURN_STRING( CODEC_ID_ATRAC3 );
                CASE_RETURN_STRING( CODEC_ID_VOXWARE );
                CASE_RETURN_STRING( CODEC_ID_APE );
                CASE_RETURN_STRING( CODEC_ID_NELLYMOSER );
                CASE_RETURN_STRING( CODEC_ID_MUSEPACK8 );
                CASE_RETURN_STRING( CODEC_ID_SPEEX );
                CASE_RETURN_STRING( CODEC_ID_WMAVOICE );
                CASE_RETURN_STRING( CODEC_ID_WMAPRO );
                CASE_RETURN_STRING( CODEC_ID_WMALOSSLESS );
                CASE_RETURN_STRING( CODEC_ID_ATRAC3P );
                CASE_RETURN_STRING( CODEC_ID_EAC3 );
                CASE_RETURN_STRING( CODEC_ID_SIPR );
                CASE_RETURN_STRING( CODEC_ID_MP1 );
                CASE_RETURN_STRING( CODEC_ID_DVD_SUBTITLE );
                CASE_RETURN_STRING( CODEC_ID_DVB_SUBTITLE );
                CASE_RETURN_STRING( CODEC_ID_TEXT );
                CASE_RETURN_STRING( CODEC_ID_XSUB );
                CASE_RETURN_STRING( CODEC_ID_SSA );
                CASE_RETURN_STRING( CODEC_ID_MOV_TEXT );
                CASE_RETURN_STRING( CODEC_ID_TTF );
                CASE_RETURN_STRING( CODEC_ID_PROBE );
                CASE_RETURN_STRING( CODEC_ID_MPEG2TS );
                CASE_RETURN_STRING( CODEC_ID_INDEO3 );
#if LIBAVCODEC_VERSION_MAJOR < 52
                CASE_RETURN_STRING( CODEC_ID_PICTOR );
                CASE_RETURN_STRING( CODEC_ID_ANSI );
                CASE_RETURN_STRING( CODEC_ID_SRT );
#endif
#if LIBAVCODEC_VERSION_MAJOR >= 52
        #if LIBAVCODEC_VERSION_MINOR >= 32
                CASE_RETURN_STRING( CODEC_ID_AURA );
                CASE_RETURN_STRING( CODEC_ID_AURA2 );
                CASE_RETURN_STRING( CODEC_ID_V210X );
                CASE_RETURN_STRING( CODEC_ID_TMV );
                CASE_RETURN_STRING( CODEC_ID_V210 );
                CASE_RETURN_STRING( CODEC_ID_DPX );
                CASE_RETURN_STRING( CODEC_ID_MAD );
                CASE_RETURN_STRING( CODEC_ID_FRWU );
                CASE_RETURN_STRING( CODEC_ID_FLASHSV2 );
                CASE_RETURN_STRING( CODEC_ID_PCM_BLURAY );
                CASE_RETURN_STRING( CODEC_ID_TWINVQ );
                CASE_RETURN_STRING( CODEC_ID_TRUEHD );
                CASE_RETURN_STRING( CODEC_ID_MP4ALS );
                CASE_RETURN_STRING( CODEC_ID_ATRAC1 );
                CASE_RETURN_STRING( CODEC_ID_HDMV_PGS_SUBTITLE );
                CASE_RETURN_STRING( CODEC_ID_DVB_TELETEXT );
        #endif
        #if LIBAVCODEC_VERSION_MINOR >= 72
                CASE_RETURN_STRING( CODEC_ID_CDGRAPHICS );
                CASE_RETURN_STRING( CODEC_ID_R210 );
                CASE_RETURN_STRING( CODEC_ID_ANM );
                CASE_RETURN_STRING( CODEC_ID_BINKVIDEO );
                CASE_RETURN_STRING( CODEC_ID_IFF_ILBM );
                CASE_RETURN_STRING( CODEC_ID_IFF_BYTERUN1 );
                CASE_RETURN_STRING( CODEC_ID_KGV1 );
                CASE_RETURN_STRING( CODEC_ID_YOP );
                CASE_RETURN_STRING( CODEC_ID_VP8 );
                CASE_RETURN_STRING( CODEC_ID_BINKAUDIO_RDFT );
                CASE_RETURN_STRING( CODEC_ID_BINKAUDIO_DCT );
        #endif
        #if LIBAVCODEC_VERSION_MINOR >= 108
                CASE_RETURN_STRING( CODEC_ID_PICTOR );
                CASE_RETURN_STRING( CODEC_ID_ANSI );
                CASE_RETURN_STRING( CODEC_ID_A64_MULTI );
                CASE_RETURN_STRING( CODEC_ID_A64_MULTI5 );
                CASE_RETURN_STRING( CODEC_ID_R10K );
                CASE_RETURN_STRING( CODEC_ID_MXPEG );
                CASE_RETURN_STRING( CODEC_ID_LAGARITH );
                CASE_RETURN_STRING( CODEC_ID_PCM_LXF );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_G722 );
                CASE_RETURN_STRING( CODEC_ID_AAC_LATM );
                CASE_RETURN_STRING( CODEC_ID_SRT );
                CASE_RETURN_STRING( CODEC_ID_FFMETADATA );

                CASE_RETURN_STRING( CODEC_ID_PRORES );
                CASE_RETURN_STRING( CODEC_ID_JV );
                CASE_RETURN_STRING( CODEC_ID_DFA );
                //CASE_RETURN_STRING( CODEC_ID_S302M );
                CASE_RETURN_STRING( CODEC_ID_QDMC );
                //CASE_RETURN_STRING( CODEC_ID_CELT );
                CASE_RETURN_STRING( CODEC_ID_MICRODVD );
        #endif
#endif

#if LIBAVCODEC_VERSION_MAJOR >= 53
                //CASE_RETURN_STRING( CODEC_ID_8SVX_RAW );

        #if LIBAVCODEC_VERSION_MINOR >= 5
                CASE_RETURN_STRING( CODEC_ID_AURA );
                CASE_RETURN_STRING( CODEC_ID_AURA2 );
                CASE_RETURN_STRING( CODEC_ID_V210X );
                CASE_RETURN_STRING( CODEC_ID_TMV );
                CASE_RETURN_STRING( CODEC_ID_V210 );
                CASE_RETURN_STRING( CODEC_ID_DPX );
                CASE_RETURN_STRING( CODEC_ID_MAD );
                CASE_RETURN_STRING( CODEC_ID_FRWU );
                CASE_RETURN_STRING( CODEC_ID_FLASHSV2 );
                CASE_RETURN_STRING( CODEC_ID_CDGRAPHICS );
                CASE_RETURN_STRING( CODEC_ID_R210 );
                CASE_RETURN_STRING( CODEC_ID_ANM );
                CASE_RETURN_STRING( CODEC_ID_BINKVIDEO );
                CASE_RETURN_STRING( CODEC_ID_IFF_ILBM );
                CASE_RETURN_STRING( CODEC_ID_IFF_BYTERUN1 );
                CASE_RETURN_STRING( CODEC_ID_KGV1 );
                CASE_RETURN_STRING( CODEC_ID_YOP );
                CASE_RETURN_STRING( CODEC_ID_VP8 );
                CASE_RETURN_STRING( CODEC_ID_PICTOR );
                CASE_RETURN_STRING( CODEC_ID_ANSI );
                CASE_RETURN_STRING( CODEC_ID_A64_MULTI );
                CASE_RETURN_STRING( CODEC_ID_A64_MULTI5 );
                CASE_RETURN_STRING( CODEC_ID_R10K );
                CASE_RETURN_STRING( CODEC_ID_MXPEG );
                CASE_RETURN_STRING( CODEC_ID_LAGARITH );
                CASE_RETURN_STRING( CODEC_ID_PRORES );
                CASE_RETURN_STRING( CODEC_ID_JV );
                CASE_RETURN_STRING( CODEC_ID_DFA );
                CASE_RETURN_STRING( CODEC_ID_PCM_BLURAY );
                CASE_RETURN_STRING( CODEC_ID_PCM_LXF );
                CASE_RETURN_STRING( CODEC_ID_S302M );
                CASE_RETURN_STRING( CODEC_ID_ADPCM_G722 );
                CASE_RETURN_STRING( CODEC_ID_TWINVQ );
                CASE_RETURN_STRING( CODEC_ID_TRUEHD );
                CASE_RETURN_STRING( CODEC_ID_MP4ALS );
                CASE_RETURN_STRING( CODEC_ID_ATRAC1 );
                CASE_RETURN_STRING( CODEC_ID_BINKAUDIO_RDFT );
                CASE_RETURN_STRING( CODEC_ID_BINKAUDIO_DCT );
                CASE_RETURN_STRING( CODEC_ID_AAC_LATM );
                CASE_RETURN_STRING( CODEC_ID_QDMC );
                CASE_RETURN_STRING( CODEC_ID_HDMV_PGS_SUBTITLE );
                CASE_RETURN_STRING( CODEC_ID_DVB_TELETEXT );
                CASE_RETURN_STRING( CODEC_ID_SRT );
                CASE_RETURN_STRING( CODEC_ID_FFMETADATA );
        #endif
#endif
        }
        return "CODEC_ID not handle.";
}

const std::string FFmpeg::codecType_toString( const AVMediaType codec_type )
{
        switch( codec_type )
        {
                case AVMEDIA_TYPE_VIDEO:
                        return "AVMEDIA_TYPE_VIDEO";
                case AVMEDIA_TYPE_AUDIO:
                        return "AVMEDIA_TYPE_AUDIO";
                case AVMEDIA_TYPE_UNKNOWN:
                        return "AVMEDIA_TYPE_UNKNOWN";
                case AVMEDIA_TYPE_DATA:
                        return "AVMEDIA_TYPE_DATA";
                case AVMEDIA_TYPE_SUBTITLE:
                        return "AVMEDIA_TYPE_SUBTITLE";
                case AVMEDIA_TYPE_ATTACHMENT:
                        return "AVMEDIA_TYPE_ATTACHMENT";
                case AVMEDIA_TYPE_NB:
                        return "AVMEDIA_TYPE_NB";
        }
        return "CODEC_TYPE not handle.";
}

const std::string FFmpeg::pixelFormat_toString( const PixelFormat p )
{
        return avcodec_get_pix_fmt_name( p );
        /*
           switch( p )
           {
                CASE_RETURN_STRING( PIX_FMT_NONE );
                CASE_RETURN_STRING( PIX_FMT_YUV420P );
                CASE_RETURN_STRING( PIX_FMT_YUYV422 );
                CASE_RETURN_STRING( PIX_FMT_RGB24 );
                CASE_RETURN_STRING( PIX_FMT_BGR24 );
                CASE_RETURN_STRING( PIX_FMT_YUV422P );
                CASE_RETURN_STRING( PIX_FMT_YUV444P );
                CASE_RETURN_STRING( PIX_FMT_RGB32 );
                CASE_RETURN_STRING( PIX_FMT_YUV410P );
                CASE_RETURN_STRING( PIX_FMT_YUV411P );
                CASE_RETURN_STRING( PIX_FMT_RGB565 );
                CASE_RETURN_STRING( PIX_FMT_RGB555 );
                CASE_RETURN_STRING( PIX_FMT_GRAY8 );
                CASE_RETURN_STRING( PIX_FMT_MONOWHITE );
                CASE_RETURN_STRING( PIX_FMT_MONOBLACK );
                CASE_RETURN_STRING( PIX_FMT_PAL8 );
                CASE_RETURN_STRING( PIX_FMT_YUVJ420P );
                CASE_RETURN_STRING( PIX_FMT_YUVJ422P );
                CASE_RETURN_STRING( PIX_FMT_YUVJ444P );
                CASE_RETURN_STRING( PIX_FMT_XVMC_MPEG2_MC );
                CASE_RETURN_STRING( PIX_FMT_XVMC_MPEG2_IDCT );
                CASE_RETURN_STRING( PIX_FMT_UYVY422 );
                CASE_RETURN_STRING( PIX_FMT_UYYVYY411 );
                CASE_RETURN_STRING( PIX_FMT_BGR32 );
                CASE_RETURN_STRING( PIX_FMT_BGR565 );
                CASE_RETURN_STRING( PIX_FMT_BGR555 );
                CASE_RETURN_STRING( PIX_FMT_BGR8 );
                CASE_RETURN_STRING( PIX_FMT_BGR4 );
                CASE_RETURN_STRING( PIX_FMT_BGR4_BYTE );
                CASE_RETURN_STRING( PIX_FMT_RGB8 );
                CASE_RETURN_STRING( PIX_FMT_RGB4 );
                CASE_RETURN_STRING( PIX_FMT_RGB4_BYTE );
                CASE_RETURN_STRING( PIX_FMT_NV12 );
                CASE_RETURN_STRING( PIX_FMT_NV21 );
                CASE_RETURN_STRING( PIX_FMT_RGB32_1 );
                CASE_RETURN_STRING( PIX_FMT_BGR32_1 );
                CASE_RETURN_STRING( PIX_FMT_GRAY16BE );
                CASE_RETURN_STRING( PIX_FMT_GRAY16LE );
                CASE_RETURN_STRING( PIX_FMT_YUV440P );
                CASE_RETURN_STRING( PIX_FMT_YUVJ440P );
                CASE_RETURN_STRING( PIX_FMT_YUVA420P );
                CASE_RETURN_STRING( PIX_FMT_VDPAU_H264 );
                CASE_RETURN_STRING( PIX_FMT_VDPAU_MPEG1 );
                CASE_RETURN_STRING( PIX_FMT_VDPAU_MPEG2 );
                CASE_RETURN_STRING( PIX_FMT_VDPAU_WMV3 );
                CASE_RETURN_STRING( PIX_FMT_VDPAU_VC1 );
                CASE_RETURN_STRING( PIX_FMT_RGB48BE );
                CASE_RETURN_STRING( PIX_FMT_RGB48LE );
                CASE_RETURN_STRING( PIX_FMT_VAAPI_MOCO );
                CASE_RETURN_STRING( PIX_FMT_VAAPI_IDCT );
                CASE_RETURN_STRING( PIX_FMT_VAAPI_VLD );
                CASE_RETURN_STRING( PIX_FMT_NB );
           }
           return "Error PixelFormat not handle.";
         */
}


/*
 #define VALUE_AND_NAME(e) e, #e

   std::map<int, std::string> formats = boost::assign::map_list_of
   ( VALUE_AND_NAME( PIX_FMT_NONE ) )
   ( VALUE_AND_NAME( PIX_FMT_YUV420P ) )
   ( VALUE_AND_NAME( PIX_FMT_YUYV422 ) )
   ( VALUE_AND_NAME( PIX_FMT_RGB24 ) )
   ( VALUE_AND_NAME( PIX_FMT_BGR24 ) )
   ( VALUE_AND_NAME( PIX_FMT_YUV422P ) )
   ( VALUE_AND_NAME( PIX_FMT_YUV444P ) )
   ( VALUE_AND_NAME( PIX_FMT_RGB32 ) )
   ( VALUE_AND_NAME( PIX_FMT_YUV410P ) )
   ( VALUE_AND_NAME( PIX_FMT_YUV411P ) )
   ( VALUE_AND_NAME( PIX_FMT_RGB565 ) )
   ( VALUE_AND_NAME( PIX_FMT_RGB555 ) )
   ( VALUE_AND_NAME( PIX_FMT_GRAY8 ) )
   ( VALUE_AND_NAME( PIX_FMT_MONOWHITE ) )
   ( VALUE_AND_NAME( PIX_FMT_MONOBLACK ) )
   ( VALUE_AND_NAME( PIX_FMT_PAL8 ) )
   ( VALUE_AND_NAME( PIX_FMT_YUVJ420P ) )
   ( VALUE_AND_NAME( PIX_FMT_YUVJ422P ) )
   ( VALUE_AND_NAME( PIX_FMT_YUVJ444P ) )
   ( VALUE_AND_NAME( PIX_FMT_XVMC_MPEG2_MC ) )
   ( VALUE_AND_NAME( PIX_FMT_XVMC_MPEG2_IDCT ) )
   ( VALUE_AND_NAME( PIX_FMT_UYVY422 ) )
   ( VALUE_AND_NAME( PIX_FMT_UYYVYY411 ) )
   ( VALUE_AND_NAME( PIX_FMT_BGR32 ) )
   ( VALUE_AND_NAME( PIX_FMT_BGR565 ) )
   ( VALUE_AND_NAME( PIX_FMT_BGR555 ) )
   ( VALUE_AND_NAME( PIX_FMT_BGR8 ) )
   ( VALUE_AND_NAME( PIX_FMT_BGR4 ) )
   ( VALUE_AND_NAME( PIX_FMT_BGR4_BYTE ) )
   ( VALUE_AND_NAME( PIX_FMT_RGB8 ) )
   ( VALUE_AND_NAME( PIX_FMT_RGB4 ) )
   ( VALUE_AND_NAME( PIX_FMT_RGB4_BYTE ) )
   ( VALUE_AND_NAME( PIX_FMT_NV12 ) )
   ( VALUE_AND_NAME( PIX_FMT_NV21 ) )

   ( VALUE_AND_NAME( PIX_FMT_RGB32_1 ) )
   ( VALUE_AND_NAME( PIX_FMT_BGR32_1 ) )

   ( VALUE_AND_NAME( PIX_FMT_GRAY16BE ) )
   ( VALUE_AND_NAME( PIX_FMT_GRAY16LE ) )
   ( VALUE_AND_NAME( PIX_FMT_YUV440P ) )
   ( VALUE_AND_NAME( PIX_FMT_YUVJ440P ) )
   ( VALUE_AND_NAME( PIX_FMT_YUVA420P ) )
   ( VALUE_AND_NAME( PIX_FMT_VDPAU_H264 ) )
   ( VALUE_AND_NAME( PIX_FMT_VDPAU_MPEG1 ) )
   ( VALUE_AND_NAME( PIX_FMT_VDPAU_MPEG2 ) )
   ( VALUE_AND_NAME( PIX_FMT_VDPAU_WMV3 ) )
   ( VALUE_AND_NAME( PIX_FMT_VDPAU_VC1 ) )
   ( VALUE_AND_NAME( PIX_FMT_RGB48BE ) )
   ( VALUE_AND_NAME( PIX_FMT_RGB48LE ) )
   ( VALUE_AND_NAME( PIX_FMT_VAAPI_MOCO ) )
   ( VALUE_AND_NAME( PIX_FMT_VAAPI_IDCT ) )
   ( VALUE_AND_NAME( PIX_FMT_VAAPI_VLD ) )
   ( VALUE_AND_NAME( PIX_FMT_NB ) );
 */

