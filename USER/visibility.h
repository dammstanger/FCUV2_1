/****************************************************************************
 *
 *   Copyright (C) 2012 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file visibility.h
 *
 * Definitions controlling symbol naming and visibility.
 *
 * This file is normally included automatically by the build system.
 */

#ifndef __SYSTEMLIB_VISIBILITY_H
#define __SYSTEMLIB_VISIBILITY_H

#ifdef __EXPORT
#  undef __EXPORT
#endif
#define __EXPORT __attribute__ ((visibility ("default")))   //对特定函数的可见性进行设置

#ifdef __PRIVATE
#  undef __PRIVATE
#endif
#define __PRIVATE __attribute__ ((visibility ("hidden")))

#ifdef __cplusplus
#  define __BEGIN_DECLS		extern "C" {
#  define __END_DECLS		}
#else
#  define __BEGIN_DECLS
#  define __END_DECLS
#endif
#endif

#ifndef NULL
#ifdef __cplusplus  

#define NULL    0  

#else  

#define NULL    ((void *)0) 

#endif

#endif //end ifndef NULL
