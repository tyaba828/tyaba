#pragma once

class Rect;
class Point;

//���f�B�A�t�@�C�����J���֐�
unsigned short OpenMediaFile(const char * file);

//�J�������f�B�A�t�@�C�����Đ�����֐�
void OpenMediaFilePlay(unsigned short mediaID);

//�J�������f�B�A�t�@�C�����~����֐�
void OpenMediaFileStop(unsigned short mediaID);

//���f�B�A�t�@�C�������֐�
void CloseMediaFile(unsigned short mediaID);


// ��`�����ɓ_���܂܂�Ă���ꍇ�� true ��Ԃ��܂��B
bool PointInRect(const Rect & rect, const Point & point);
