// Copyright (C) 2004 Id Software, Inc.
//
/*
sys_event.h

Event are used for scheduling tasks and for linking script commands.
*/
#ifndef __SYS_EVENT_H__
#define __SYS_EVENT_H__

#define D_EVENT_MAXARGS				8			// if changed, enable the CREATE_EVENT_CODE define in Event.cpp to generate switch statement for idClass::ProcessEventArgPtr.
												// running the game will then generate c:\doom\base\events.txt, the contents of which should be copied into the switch statement.

#define D_EVENT_VOID				( ( char )0 )
#define D_EVENT_INTEGER				'd'
#define D_EVENT_FLOAT				'f'
#define D_EVENT_VECTOR				'v'
#define D_EVENT_STRING				's'
#define D_EVENT_ENTITY				'e'
#define	D_EVENT_ENTITY_NULL			'E'			// event can handle NULL entity pointers
#define D_EVENT_TRACE				't'

#define MAX_EVENTS					4096

#ifdef _PREY
#if defined(__aarch64__) || defined(__x86_64__)
#define D_EVENT_INTPTR		'y'
#endif
#endif
// stack size of idVec3, aligned to native pointer size
#define E_EVENT_SIZEOF_VEC			((sizeof(idVec3) + (sizeof(intptr_t) - 1)) & ~(sizeof(intptr_t) - 1))

//HUMANHEAD: aob - needed for networking to send the least amount of bits
extern const int MAX_EVENTS_NUM_BITS;
//HUMANHEAD END

class idClass;
class idTypeInfo;

class idEventDef {
private:
	const char					*name;
	const char					*formatspec;
	unsigned int				formatspecIndex;
	int							returnType;
	int							numargs;
	size_t						argsize;
	int							argOffset[ D_EVENT_MAXARGS ];
	int							eventnum;
	const idEventDef *			next;

	static idEventDef *			eventDefList[MAX_EVENTS];
	static int					numEventDefs;

public:
								idEventDef( const char *command, const char *formatspec = NULL, char returnType = 0 );
								
	const char					*GetName( void ) const;
	const char					*GetArgFormat( void ) const;
	unsigned int				GetFormatspecIndex( void ) const;
	int							GetReturnType( void ) const;
	int							GetEventNum( void ) const;
	int							GetNumArgs( void ) const;
	size_t						GetArgSize( void ) const;
	int							GetArgOffset( int arg ) const;

	static int					NumEventCommands( void );
	static const idEventDef		*GetEventCommand( int eventnum );
	static const idEventDef		*FindEvent( const char *name );

	//HUMANHEAD: aob
	static const idEventDef		*FindEvent( int eventId );
	//HUMANHEAD END
};

class idSaveGame;
class idRestoreGame;

class idEvent {
private:
	const idEventDef			*eventdef;
	byte						*data;
	int							time;
	idClass						*object;
	const idTypeInfo			*typeinfo;

	idLinkList<idEvent>			eventNode;

	static idDynamicBlockAlloc<byte, 16 * 1024, 256> eventDataAllocator;


public:
	static bool					initialized;

								~idEvent();

	static idEvent				*Alloc( const idEventDef *evdef, int numargs, va_list args );
	static void					CopyArgs( const idEventDef *evdef, int numargs, va_list args, intptr_t data[ D_EVENT_MAXARGS ]  );
	
	void						Free( void );
	void						Schedule( idClass *object, const idTypeInfo *cls, int time );
	byte						*GetData( void );

	// HUMANHEAD pdm
	static int					NumQueuedEvents( const idClass *obj, const idEventDef *evdef = NULL );
	// HUMANHEAD END

	static void					CancelEvents( const idClass *obj, const idEventDef *evdef = NULL );
	static void					ClearEventList( void );
	static void					ServiceEvents( void );
	static void					Init( void );
	static void					Shutdown( void );

	// save games
	static void					Save( idSaveGame *savefile );					// archives object for save game file
	static void					Restore( idRestoreGame *savefile );				// unarchives object from save game file
	static void					SaveTrace( idSaveGame *savefile, const trace_t &trace );
	static void					RestoreTrace( idRestoreGame *savefile, trace_t &trace );
	
};

/*
================
idEvent::GetData
================
*/
ID_INLINE byte *idEvent::GetData( void ) {
	return data;
}

/*
================
idEventDef::GetName
================
*/
ID_INLINE const char *idEventDef::GetName( void ) const {
	return name;
}

/*
================
idEventDef::GetArgFormat
================
*/
ID_INLINE const char *idEventDef::GetArgFormat( void ) const {
	return formatspec;
}

/*
================
idEventDef::GetFormatspecIndex
================
*/
ID_INLINE unsigned int idEventDef::GetFormatspecIndex( void ) const {
	return formatspecIndex;
}

/*
================
idEventDef::GetReturnType
================
*/
ID_INLINE int idEventDef::GetReturnType( void ) const {
	return returnType;
}

/*
================
idEventDef::GetNumArgs
================
*/
ID_INLINE int idEventDef::GetNumArgs( void ) const {
	return numargs;
}

/*
================
idEventDef::GetArgSize
================
*/
ID_INLINE size_t idEventDef::GetArgSize( void ) const {
	return argsize;
}

/*
================
idEventDef::GetArgOffset
================
*/
ID_INLINE int idEventDef::GetArgOffset( int arg ) const {
	assert( ( arg >= 0 ) && ( arg < D_EVENT_MAXARGS ) );
	return argOffset[ arg ];
}

/*
================
idEventDef::GetEventNum
================
*/
ID_INLINE int idEventDef::GetEventNum( void ) const {
	return eventnum;
}

#endif /* !__SYS_EVENT_H__ */
