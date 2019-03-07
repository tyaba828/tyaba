#pragma once

class Rect;
class Point;

//メディアファイルを開く関数
unsigned short OpenMediaFile(const char * file);

//開いたメディアファイルを再生する関数
void OpenMediaFilePlay(unsigned short mediaID);

//開いたメディアファイルを停止する関数
void OpenMediaFileStop(unsigned short mediaID);

//メディアファイルを閉じる関数
void CloseMediaFile(unsigned short mediaID);


// 矩形内部に点が含まれている場合は true を返します。
bool PointInRect(const Rect & rect, const Point & point);
