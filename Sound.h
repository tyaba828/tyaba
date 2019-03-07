#pragma once

//�T�E���h�V�X�e��������������֐�
void StartupSoundSystem();
//�T�E���h�V�X�e�����I������֐�
void ShutdownSoundSystem();

// �w�肳�ꂽ�T�E���h�t�@�C�����J���A�Đ��\�ȏ�Ԃɂ��܂��B
// ��1���� path : 
// �߂�l : �T�E���h�̎��ʔԍ�
unsigned short OpenSound(const char * path);

// �w�肳�ꂽ�T�E���h�t�@�C�����Đ����܂��B
// ��1���� soundID : �Đ��������T�E���h�̎��ʔԍ�
void PlaySound2(unsigned short soundID, int loopTimes = 1, bool autoClose = false);

// �w�肳�ꂽ�T�E���h�t�@�C�����~���܂��B
// ��1���� soundID : ��~�������T�E���h�̎��ʔԍ�
void StopSound(unsigned short soundID);

// �w�肳�ꂽ�T�E���h�t�@�C������܂��B
// ��1���� soundID : �������T�E���h�̎��ʔԍ�
void CloseSound(unsigned short soundID);


