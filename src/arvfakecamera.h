/* Aravis - Digital camera library
 *
 * Copyright © 2009-2019 Emmanuel Pacaud
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 * Author: Emmanuel Pacaud <emmanuel@gnome.org>
 */

#ifndef ARV_FAKE_CAMERA_H
#define ARV_FAKE_CAMERA_H

#if !defined (ARV_H_INSIDE) && !defined (ARAVIS_COMPILATION)
#error "Only <arv.h> can be included directly."
#endif

#include <v4l2-capture/v4l2-capture.h>
#include <arvbuffer.h>
#include <gio/gio.h>

G_BEGIN_DECLS

void arv_set_fake_camera_genicam_filename (const char *filename);

#define ARV_FAKE_CAMERA_MEMORY_SIZE	0x10000

/* To keep in sync with arv-fake-camera.xml */

#define ARV_FAKE_CAMERA_VENDOR				"Xinity"
#define ARV_FAKE_CAMERA_MODEL				"TrueLand"

/* Image format control */

#define ARV_FAKE_CAMERA_REGISTER_SENSOR_WIDTH		0x11c
#define ARV_FAKE_CAMERA_REGISTER_SENSOR_HEIGHT		0x118
#define ARV_FAKE_CAMERA_REGISTER_WIDTH			0x100
#define ARV_FAKE_CAMERA_REGISTER_HEIGHT			0x104
#define ARV_FAKE_CAMERA_REGISTER_X_OFFSET		0x130
#define ARV_FAKE_CAMERA_REGISTER_Y_OFFSET		0x134
#define ARV_FAKE_CAMERA_REGISTER_BINNING_HORIZONTAL	0x108
#define ARV_FAKE_CAMERA_REGISTER_BINNING_VERTICAL	0x10c
#define ARV_FAKE_CAMERA_REGISTER_PIXEL_FORMAT		0x128
#define ARV_FAKE_CAMERA_REGISTER_TEST			0x1f0

#define ARV_FAKE_CAMERA_SENSOR_WIDTH			2048
#define ARV_FAKE_CAMERA_SENSOR_HEIGHT			2048
#define ARV_FAKE_CAMERA_WIDTH_DEFAULT			V4L2_WIDTH_DEFAULT
#define ARV_FAKE_CAMERA_HEIGHT_DEFAULT			V4L2_HEIGHT_DEFAULT
#define ARV_FAKE_CAMERA_BINNING_HORIZONTAL_DEFAULT	0
#define ARV_FAKE_CAMERA_BINNING_VERTICAL_DEFAULT	0
#define ARV_FAKE_CAMERA_PIXEL_FORMAT_DEFAULT		ARV_PIXEL_FORMAT_YUV_422_YUYV_PACKED
#define ARV_FAKE_CAMERA_TEST_REGISTER_DEFAULT		0x12345678

/* Acquisition control */

#define ARV_FAKE_CAMERA_REGISTER_ACQUISITION_MODE	0x12c

#define ARV_FAKE_CAMERA_REGISTER_ACQUISITION_FRAME_PERIOD_US	0x138

#define ARV_FAKE_CAMERA_REGISTER_FRAME_START_OFFSET		0x000
#define ARV_FAKE_CAMERA_REGISTER_ACQUISITION_START_OFFSET	0x020

#define ARV_FAKE_CAMERA_REGISTER_TRIGGER_MODE		0x300
#define ARV_FAKE_CAMERA_REGISTER_TRIGGER_SOURCE		0x304
#define ARV_FAKE_CAMERA_REGISTER_TRIGGER_ACTIVATION	0x308

#define ARV_FAKE_CAMERA_REGISTER_ACQUISITION		0x124
#define ARV_FAKE_CAMERA_REGISTER_EXPOSURE_TIME_US	0x120

#define ARV_FAKE_CAMERA_ACQUISITION_FRAME_RATE_DEFAULT	25.0
#define ARV_FAKE_CAMERA_EXPOSURE_TIME_US_DEFAULT	10000.0

/* Analog control */

#define ARV_FAKE_CAMERA_REGISTER_GAIN_RAW		0x110
#define ARV_FAKE_CAMERA_REGISTER_GAIN_MODE		0x114

#define ARV_TYPE_FAKE_CAMERA             (arv_fake_camera_get_type ())
G_DECLARE_FINAL_TYPE (ArvFakeCamera, arv_fake_camera, ARV, FAKE_CAMERA, GObject)

typedef void (*ArvFakeCameraFillPattern) (ArvBuffer *buffer, void *fill_pattern_data,
					  guint32 exposure_time_us, guint32 gain,
					  ArvPixelFormat pixel_format);

ArvFakeCamera * arv_fake_camera_new 		(const char *serial_number);
ArvFakeCamera * arv_fake_camera_new_full 	(const char *serial_number, const char *genicam_filename);
gboolean	arv_fake_camera_read_memory 	(ArvFakeCamera *camera, guint32 address, guint32 size, void *buffer);
gboolean	arv_fake_camera_write_memory	(ArvFakeCamera *camera, guint32 address, guint32 size,
						 const void *buffer);
gboolean 	arv_fake_camera_read_register	(ArvFakeCamera *camera, guint32 address, guint32 *value);
gboolean	arv_fake_camera_write_register 	(ArvFakeCamera *camera, guint32 address, guint32 value);

size_t 		arv_fake_camera_get_payload 		(ArvFakeCamera *camera);
void 		arv_fake_camera_wait_for_next_frame 	(ArvFakeCamera *camera);
guint64 	arv_fake_camera_get_sleep_time_for_next_frame 	(ArvFakeCamera *camera, guint64 *next_timestamp_us);
void		arv_fake_camera_fill_buffer		(ArvFakeCamera *camera, ArvBuffer *buffer,
							 guint32 *packet_size);

guint32 	arv_fake_camera_get_acquisition_status 	(ArvFakeCamera *camera);
GSocketAddress *arv_fake_camera_get_stream_address 	(ArvFakeCamera *camera);
void		arv_fake_camera_set_inet_address	(ArvFakeCamera *camera, GInetAddress *address);

guint32		arv_fake_camera_get_control_channel_privilege	(ArvFakeCamera *camera);
void		arv_fake_camera_set_control_channel_privilege	(ArvFakeCamera *camera, guint32 privilege);
guint32		arv_fake_camera_get_heartbeat_timeout		(ArvFakeCamera *camera);

void		arv_fake_camera_set_fill_pattern	(ArvFakeCamera *camera,
							 ArvFakeCameraFillPattern fill_pattern_callback,
							 void *fill_pattern_data);
void 		arv_fake_camera_set_trigger_frequency 	(ArvFakeCamera *camera, double frequency);

const char *	arv_fake_camera_get_genicam_xml 	(ArvFakeCamera *camera, size_t *size);

G_END_DECLS

#endif

