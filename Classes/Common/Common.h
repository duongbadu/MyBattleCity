#ifndef _Common_H_
#define _Common_H_

/**
*	@brief : ������ȫ�ֶ���
*/
#include <vector>
#include <unordered_map>
#include <string>

//��ͼ����ö��
typedef enum
{
	//�յ�ͼ
	MapNone,
	//��
	MapGrass,
	//ǽ
	MapWall,
	//��
	MapSteel,
	//����
	MapRiver,
	//��
	MapHome
}TiledMapType;


/**
*	@brief : ���ڵ�ͼ����ײ���
*/
static std::unordered_map<int, TiledMapType> gid2Type = {
	
	{ 5, MapSteel },
	{ 6, MapSteel },
	{ 11, MapSteel },
	{ 12, MapSteel },

	{ 13, MapWall },
	{ 14, MapWall },
	{ 19, MapWall },
	{ 20, MapWall },

	{ 15, MapRiver },
	{ 16, MapRiver },
	{ 21, MapRiver },
	{ 22, MapRiver },

	{ 17, MapHome },
	{ 18, MapHome },
	{ 23, MapHome },
	{ 24, MapHome },
};



#endif