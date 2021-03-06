/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2015 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU Lesser General Public License Version 2.1
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include "config.h"

#include "fwupd-enums.h"

/**
 * fwupd_status_to_string:
 *
 * Since: 0.1.1
 **/
const gchar *
fwupd_status_to_string (FwupdStatus status)
{
	if (status == FWUPD_STATUS_IDLE)
		return "idle";
	if (status == FWUPD_STATUS_DECOMPRESSING)
		return "decompressing";
	if (status == FWUPD_STATUS_LOADING)
		return "loading";
	if (status == FWUPD_STATUS_DEVICE_RESTART)
		return "device-restart";
	if (status == FWUPD_STATUS_DEVICE_WRITE)
		return "device-write";
	if (status == FWUPD_STATUS_DEVICE_VERIFY)
		return "device-verify";
	if (status == FWUPD_STATUS_SCHEDULING)
		return "scheduling";
	return NULL;
}

/**
 * fwupd_status_from_string:
 *
 * Since: 0.1.1
 **/
FwupdStatus
fwupd_status_from_string (const gchar *status)
{
	if (g_strcmp0 (status, "idle") == 0)
		return FWUPD_STATUS_IDLE;
	if (g_strcmp0 (status, "decompressing") == 0)
		return FWUPD_STATUS_DECOMPRESSING;
	if (g_strcmp0 (status, "loading") == 0)
		return FWUPD_STATUS_LOADING;
	if (g_strcmp0 (status, "device-restart") == 0)
		return FWUPD_STATUS_DEVICE_RESTART;
	if (g_strcmp0 (status, "device-write") == 0)
		return FWUPD_STATUS_DEVICE_WRITE;
	if (g_strcmp0 (status, "device-verify") == 0)
		return FWUPD_STATUS_DEVICE_VERIFY;
	if (g_strcmp0 (status, "scheduling") == 0)
		return FWUPD_STATUS_SCHEDULING;
	return FWUPD_STATUS_IDLE;
}
