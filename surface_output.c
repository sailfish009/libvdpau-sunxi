/*
 * Copyright (c) 2013 Jens Kuske <jenskuske@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "vdpau_private.h"
#include "string.h"
#include "vdpau_private.h"

VdpStatus vdp_output_surface_create(VdpDevice device, VdpRGBAFormat rgba_format, uint32_t width, uint32_t height, VdpOutputSurface  *surface)
{
   int status = VDP_STATUS_OK;
	if (!surface)
		return VDP_STATUS_INVALID_POINTER;

	if (!width || !height)
		return VDP_STATUS_INVALID_SIZE;

	device_ctx_t *dev = handle_get(device);
	if (!dev)
		return VDP_STATUS_INVALID_HANDLE;

	output_surface_ctx_t *out = handle_create(sizeof(*out), surface, htype_output);
	if (out)
        {
            memset(out, 0, sizeof(*out));
            out->width = width;
            out->height = height;
            out->rgba_format = rgba_format;
            out->contrast = 1.0;
            out->saturation = 1.0;
            out->device = dev;
        }
        else{
            status = VDP_STATUS_RESOURCES;
        }
        handle_release(device);
	return status;
}

VdpStatus vdp_output_surface_destroy(VdpOutputSurface surface)
{
	output_surface_ctx_t *out = handle_get(surface);
	if (!out)
		return VDP_STATUS_INVALID_HANDLE;

	memset(out, 0, sizeof(*out));
	
        handle_release(surface);
        handle_destroy(surface);

	return VDP_STATUS_OK;
}

VdpStatus vdp_output_surface_get_parameters(VdpOutputSurface surface, VdpRGBAFormat *rgba_format, uint32_t *width, uint32_t *height)
{
	output_surface_ctx_t *out = handle_get(surface);
	if (!out)
		return VDP_STATUS_INVALID_HANDLE;

	if (rgba_format)
		*rgba_format = out->rgba_format;

	if (width)
		*width = out->width;

	if (height)
		*height = out->height;

        handle_release(surface);
	return VDP_STATUS_OK;
}

VdpStatus vdp_output_surface_get_bits_native(VdpOutputSurface surface, VdpRect const *source_rect, void *const *destination_data, uint32_t const *destination_pitches)
{
	output_surface_ctx_t *out = handle_get(surface);
	if (!out)
		return VDP_STATUS_INVALID_HANDLE;


        handle_release(surface);
	return VDP_STATUS_ERROR;
}

VdpStatus vdp_output_surface_put_bits_native(VdpOutputSurface surface, void const *const *source_data, uint32_t const *source_pitches, VdpRect const *destination_rect)
{
	output_surface_ctx_t *out = handle_get(surface);
	if (!out)
		return VDP_STATUS_INVALID_HANDLE;

	VDPAU_DBG_ONCE("%s called but unimplemented!", __func__);


        handle_release(surface);
	return VDP_STATUS_OK;
}

VdpStatus vdp_output_surface_put_bits_indexed(VdpOutputSurface surface, VdpIndexedFormat source_indexed_format, void const *const *source_data, uint32_t const *source_pitch, VdpRect const *destination_rect, VdpColorTableFormat color_table_format, void const *color_table)
{
	output_surface_ctx_t *out = handle_get(surface);
	if (!out)
		return VDP_STATUS_INVALID_HANDLE;

	VDPAU_DBG_ONCE("%s called but unimplemented!", __func__);


        handle_release(surface);
	return VDP_STATUS_OK;
}

VdpStatus vdp_output_surface_put_bits_y_cb_cr(VdpOutputSurface surface, VdpYCbCrFormat source_ycbcr_format, void const *const *source_data, uint32_t const *source_pitches, VdpRect const *destination_rect, VdpCSCMatrix const *csc_matrix)
{
	output_surface_ctx_t *out = handle_get(surface);
	if (!out)
		return VDP_STATUS_INVALID_HANDLE;

	VDPAU_DBG_ONCE("%s called but unimplemented!", __func__);


        handle_release(surface);
	return VDP_STATUS_OK;
}

VdpStatus vdp_output_surface_render_output_surface(VdpOutputSurface destination_surface, VdpRect const *destination_rect, VdpOutputSurface source_surface, VdpRect const *source_rect, VdpColor const *colors, VdpOutputSurfaceRenderBlendState const *blend_state, uint32_t flags)
{
	output_surface_ctx_t *out = handle_get(destination_surface);
	if (!out)
		return VDP_STATUS_INVALID_HANDLE;

	output_surface_ctx_t *in = handle_get(source_surface);
	if (!in)
		return VDP_STATUS_INVALID_HANDLE;

	VDPAU_DBG_ONCE("%s called but unimplemented!", __func__);


        handle_release(destination_surface);
        handle_release(source_surface);
	return VDP_STATUS_OK;
}

VdpStatus vdp_output_surface_render_bitmap_surface(VdpOutputSurface destination_surface, VdpRect const *destination_rect, VdpBitmapSurface source_surface, VdpRect const *source_rect, VdpColor const *colors, VdpOutputSurfaceRenderBlendState const *blend_state, uint32_t flags)
{
	output_surface_ctx_t *out = handle_get(destination_surface);
	if (!out)
		return VDP_STATUS_INVALID_HANDLE;

	VDPAU_DBG_ONCE("%s called but unimplemented!", __func__);


        handle_release(destination_surface);
	return VDP_STATUS_OK;
}

VdpStatus vdp_output_surface_query_capabilities(VdpDevice device, VdpRGBAFormat surface_rgba_format, VdpBool *is_supported, uint32_t *max_width, uint32_t *max_height)
{
	if (!is_supported || !max_width || !max_height)
		return VDP_STATUS_INVALID_POINTER;

	device_ctx_t *dev = handle_get(device);
	if (!dev)
		return VDP_STATUS_INVALID_HANDLE;

	*is_supported = (surface_rgba_format == VDP_RGBA_FORMAT_R8G8B8A8 || surface_rgba_format == VDP_RGBA_FORMAT_B8G8R8A8);
	*max_width = 8192;
	*max_height = 8192;

        handle_release(device);
        
	return VDP_STATUS_OK;
}

VdpStatus vdp_output_surface_query_get_put_bits_native_capabilities(VdpDevice device, VdpRGBAFormat surface_rgba_format, VdpBool *is_supported)
{
	if (!is_supported)
		return VDP_STATUS_INVALID_POINTER;

	device_ctx_t *dev = handle_get(device);
	if (!dev)
		return VDP_STATUS_INVALID_HANDLE;

	*is_supported = VDP_FALSE;

        handle_release(device);
	return VDP_STATUS_OK;
}

VdpStatus vdp_output_surface_query_put_bits_indexed_capabilities(VdpDevice device, VdpRGBAFormat surface_rgba_format, VdpIndexedFormat bits_indexed_format, VdpColorTableFormat color_table_format, VdpBool *is_supported)
{
	if (!is_supported)
		return VDP_STATUS_INVALID_POINTER;

	device_ctx_t *dev = handle_get(device);
	if (!dev)
		return VDP_STATUS_INVALID_HANDLE;

	*is_supported = VDP_FALSE;

        handle_release(device);
	return VDP_STATUS_OK;
}

VdpStatus vdp_output_surface_query_put_bits_y_cb_cr_capabilities(VdpDevice device, VdpRGBAFormat surface_rgba_format, VdpYCbCrFormat bits_ycbcr_format, VdpBool *is_supported)
{
	if (!is_supported)
		return VDP_STATUS_INVALID_POINTER;

	device_ctx_t *dev = handle_get(device);
	if (!dev)
		return VDP_STATUS_INVALID_HANDLE;

	*is_supported = VDP_FALSE;

        handle_release(device);
	return VDP_STATUS_OK;
}
