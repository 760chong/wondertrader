#pragma once
#include <vector>
#include <unordered_set>
#include "../WtCore/IDataReader.h"
#include "../WtCore/IDataManager.h"

#include "../Share/WTSCollection.hpp"

class WtExecRunner;

NS_OTP_BEGIN
class WTSVariant;
class WTSHisTickData;
class WTSKlineData;
class WTSTickData;
class WTSKlineSlice;
class WTSTickSlice;
class IBaseDataMgr;
class IBaseDataMgr;

class WtSimpDataMgr : public IDataReaderSink, public IDataManager
{
public:
	WtSimpDataMgr();
	~WtSimpDataMgr();

private:
	bool	initStore(WTSVariant* cfg);

public:
	bool	init(WTSVariant* cfg, WtExecRunner* runner);

	void	handle_push_quote(const char* stdCode, WTSTickData* newTick);

	//////////////////////////////////////////////////////////////////////////
	//IDataManager
	WTSTickSlice* get_tick_slice(const char* code, uint32_t count) override;
	WTSKlineSlice* get_kline_slice(const char* code, WTSKlinePeriod period, uint32_t times, uint32_t count) override;
	WTSTickData* grab_last_tick(const char* code) override;

	//////////////////////////////////////////////////////////////////////////
	//IDataStoreListener
	virtual void	on_bar(const char* code, WTSKlinePeriod period, WTSBarStruct* newBar) override;
	virtual void	on_all_bar_updated(uint32_t updateTime) override;

	virtual IBaseDataMgr* get_basedata_mgr() override;
	virtual IHotMgr*	get_hot_mgr() override;
	virtual uint32_t	get_date() override;
	virtual uint32_t	get_min_time()override;
	virtual uint32_t	get_secs() override;

	virtual void		reader_log(WTSLogLevel ll, const char* fmt, ...) override;

	IDataReader* reader() { return _reader; }

private:
	IDataReader*	_reader;
	WtExecRunner*	_runner;

	typedef WTSHashMap<std::string> DataCacheMap;
	DataCacheMap* _bars_cache;	//K�߻���
	DataCacheMap* _rt_tick_map;	//ʵʱtick����

	uint32_t		_cur_date;
	uint32_t		_cur_raw_time;
	uint32_t		_cur_min_time;
	uint32_t		_cur_secs;
	uint32_t		_cur_tdate;

};

NS_OTP_END