﻿/**
 * FileName: HookDef.h
 *
 * Copyright (C) 2024 Maplespe
 *
 * This file is part of MToolBox and DWMBlurGlass.
 * DWMBlurGlass is free software: you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation, either version 3
 * of the License, or any later version.
 *
 * DWMBlurGlass is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with Foobar.
 * If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
*/
#pragma once
#include "HookHelper.h"
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <wincodec.h>
#include <dwmapi.h>
#pragma comment(lib, "d2d1.lib")

namespace MDWMBlurGlassExt
{
	struct CRenderData {};
	struct CDrawingContext {};
	struct CDrawListEntryBuilder {};
	struct MilRectF
	{
		FLOAT left;
		FLOAT top;
		FLOAT right;
		FLOAT bottom;
	};

	struct CVisualTree {};
	struct CImageSource {};
	struct CRenderingTechnique {};
	struct EffectInput {};
	struct ID2DContextOwner {};
	struct CCustomBlur {};
	struct CWindowList {};
	struct CAccent {};
	struct CBaseGeometryProxy {};
	struct CText {};
	struct CTopLevelWindow_WindowFrame {};
	struct CDWriteText {};
	struct CTopLevelWindow {};
	struct CLegacyRenderTarget {};
	struct COcclusionContext {};
	struct CWindowNode {};

	struct ACCENT_POLICY
	{
		int32_t   nAccentState;
		int32_t  nFlags;
		uint32_t nColor;
		int32_t  nAnimationId;
	};

	union GpCC
	{
		struct {
			BYTE b;
			BYTE g;
			BYTE r;
			BYTE a;
		};
		UINT32 argb;
	};

	template<class E>
	struct TMILFlagsEnum
	{
		E flags;

		TMILFlagsEnum() { }
		TMILFlagsEnum(const E& _Right) { flags = _Right; }
		TMILFlagsEnum(const int& _Right) { flags = static_cast<E>(_Right); }

		operator const E& () const { return flags; }

		TMILFlagsEnum& operator|=(const int& _Right)
		{
			flags = static_cast<E>(flags | _Right);
			return *this;
		}

		TMILFlagsEnum& operator&=(const int& _Right)
		{
			flags = static_cast<E>(flags & _Right);
			return *this;
		}

		TMILFlagsEnum& operator^=(const int& _Right)
		{
			flags = static_cast<E>(flags ^ _Right);
			return *this;
		}
	};

	enum ColorizationFlags
	{
		Color_TitleBackground,
		Color_ActiveText = 13,
		Color_InactiveText,
		Color_Unknown = 17984
	};

	HRESULT WINAPI CRenderData_DrawSolidColorRectangle
	(
		CRenderData* This,
		CDrawingContext* a2,
		CDrawListEntryBuilder* a3,
		bool a4,
		const MilRectF* a5,
		D3DCOLORVALUE* a6
	);

	DWORD64 WINAPI CRenderingTechnique_ExecuteBlur
	(
		CRenderingTechnique* This,
		CDrawingContext* a2,
		const EffectInput* a3,
		const D2D_VECTOR_2F* a4,
		EffectInput* a5
	);

	DWORD64 WINAPI CD2DContext_FillEffect
	(
		ID2D1DeviceContext** This,
		const ID2DContextOwner* a2,
		ID2D1Effect* inputEffect,
		const D2D_RECT_F* srcRect,
		const D2D_POINT_2F* dstPoint,
		D2D1_INTERPOLATION_MODE interMode,
		D2D1_COMPOSITE_MODE mode
	);

	DWORD64 WINAPI CCustomBlur_BuildEffect(
		CCustomBlur* This,
		ID2D1Image* backdropImage,
		const D2D_RECT_F* srcRect,
		const D2D_SIZE_F* kSize,
		D2D1_GAUSSIANBLUR_OPTIMIZATION a5,
		const D2D_VECTOR_2F* a6,
		D2D_VECTOR_2F* a7
	);

	float WINAPI CCustomBlur_DetermineOutputScale(
		float a1,
		float a2,
		D2D1_GAUSSIANBLUR_OPTIMIZATION a3
	);

	int WINAPI MyFillRect(
		HDC hdc,
		LPRECT rect, 
		HBRUSH hbrush
	);

	int MyDrawTextW(
		HDC     hdc,
		LPCWSTR lpchText,
		int     cchText,
		LPRECT  lprc,
		UINT    format
	);

	HRESULT WINAPI MyCreateBitmapFromHBITMAP(
		IWICImagingFactory2* This,
		HBITMAP hBitmap,
		HPALETTE hPalette,
		WICBitmapAlphaChannelOption options,
		IWICBitmap** ppIBitmap
	);

	HRESULT WINAPI CWindowList_GetExtendedFrameBounds(
		CWindowList* This,
		HWND hwnd,
		RECT* rect
	);

	DWORD64 WINAPI CTopLevelWindow_UpdateNCAreaGeometry(
		CTopLevelWindow* This
	);

	HRGN WINAPI MyCreateRoundRectRgn(
		int x1,
		int y1,
		int x2, 
		int y2, 
		int w, 
		int h
	);

	DWORD64 WINAPI CDrawingContext_FillEffect(
		CDrawingContext* This,
		ID2D1Effect* a2,
		const D2D_RECT_F* a3,
		const D2D_POINT_2F* a4,
		char a5
	);

	DWORD64 __fastcall CDrawingContext_DrawVisualTree(
		CDrawingContext* This,
		MilRectF* a2,
		MilRectF* a3,
		COcclusionContext* a4,
		int a5,
		char a6
	);

	DWORD64 WINAPI HrgnFromRects(
		const tagRECT* Src, unsigned int a2, HRGN* a3
	);

	void WINAPI CAccent_UpdateAccentBlurRect(
		CAccent* This,
		const RECT* a2
	);

	HRESULT WINAPI CAccent_UpdateAccentPolicy(
		CAccent* This,
		RECT* a2,
		ACCENT_POLICY* a3,
		CBaseGeometryProxy* a4
	);

	CTopLevelWindow_WindowFrame* WINAPI CTopLevelWindow_s_ChooseWindowFrameFromStyle(
		char a1,
		char a2,
		char a3
	);

	void WINAPI CTopLevelWindow_OnAccentPolicyUpdated(
		struct CTopLevelWindow* This
	);

	HRESULT WINAPI CTopLevelWindow_ValidateVisual(
		CTopLevelWindow* This
	);

	DWORD64 WINAPI CTopLevelWindow_UpdateWindowVisuals(
		CTopLevelWindow* This
	);

	void WINAPI CText_SetColor(
		CText* This,
		COLORREF a2
	);

	DWORD64 WINAPI CGlassColorizationParameters_AdjustWindowColorization(
		GpCC* a1,
		float a2,
		TMILFlagsEnum<ColorizationFlags> a3
	);

	DWORD64 WINAPI CTopLevelWindow_UpdateText(
		CTopLevelWindow* This,
		struct CTopLevelWindow_WindowFrame* a2,
		double a3
	);
}